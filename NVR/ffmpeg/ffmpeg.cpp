#include "ffmpeg.h"
#include <stdio.h>
#include <iostream>
using namespace std;
extern char url[];


FFMPEG::FFMPEG() : m_commonThread(this)
{
    videoStreamIndex = -1;
    audioStreamIndex = -1;

    pAVFormatContext = NULL;
    pSwsContext = NULL;
    pAVFrame = NULL;
    timeSpan = 1;
    fp = NULL;

    ofmt = NULL;
    ofmt_ctx = NULL;
}

FFMPEG::~FFMPEG()
{
}


bool FFMPEG::initService()
{
    getLocalTime();

    av_register_all();
    avformat_network_init();
    pAVFormatContext = avformat_alloc_context();
    pAVFrame = av_frame_alloc();

    m_commonThread.start(256*1024);

    return true;
}

void FFMPEG::ThreadProc()
{
    while(1)
    {
        if(openInputStream())
            openOutputStream();
        closeOutputStream();
        sleep(1);
    }

}

bool FFMPEG::IsRun()
{
    return m_commonThread.isRun();
}

bool FFMPEG::openInputStream()
{
    int result = avformat_open_input(&pAVFormatContext, url, NULL, NULL);

    if (result < 0)
    {
        printf("openInputStream result = %d\n", result);
        return false;
    }

    result = avformat_find_stream_info(pAVFormatContext, NULL);
    if (result < 0)
    {
        cout << "open stream failed";
        return false;
    }
    printf("===========Input Information==========\n");
    av_dump_format(pAVFormatContext, 0, url, 0);

    avformat_alloc_output_context2(&ofmt_ctx, NULL, "mpegts", NULL);
    if (!ofmt_ctx) {
        printf( "Could not create output context\n");
        return false;
    }
    ofmt = ofmt_ctx->oformat;


    videoStreamIndex = -1;
    audioStreamIndex = -1;

    for (uint i = 0; i < pAVFormatContext->nb_streams; i++)
    {
        if (pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO)
        {
            printf("video stream index is %d\n", i);
            videoStreamIndex = i;
            in_stream = pAVFormatContext->streams[i];
            out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
            if (!out_stream) {
                printf( "Failed allocating output stream\n");
                return false;
            }
            videoindex_out=out_stream->index;
            //Copy the settings of AVCodecContext
            if (avcodec_copy_context(out_stream->codec, in_stream->codec) < 0) {
                printf( "Failed to copy context from input to output stream codec context\n");
                return false;
            }
            out_stream->codec->codec_tag = 0;
            if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
                out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;

            break;
        }
    }

    for (uint i = 0; i < pAVFormatContext->nb_streams; i++)
    {
        if (pAVFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO)
        {
            printf("audio stream index is %d\n", i);
            audioStreamIndex = i;
            in_stream = pAVFormatContext->streams[i];
            out_stream = avformat_new_stream(ofmt_ctx, in_stream->codec->codec);
            if (!out_stream) {
                printf( "Failed allocating output stream\n");
                break;
            }
            audioindex_out=out_stream->index;
            //Copy the settings of AVCodecContext
            if (avcodec_copy_context(out_stream->codec, in_stream->codec) < 0) {
                printf( "Failed to copy context from input to output stream codec context\n");
                break;
            }
            out_stream->codec->codec_tag = 0;
            if (ofmt_ctx->oformat->flags & AVFMT_GLOBALHEADER)
                    out_stream->codec->flags |= CODEC_FLAG_GLOBAL_HEADER;

            break;
        }
    }

    printf("==========Output Information==========\n");
    av_dump_format(ofmt_ctx, 0, videoSavePath, 1);

    if (videoStreamIndex == -1)
    {
        cout << "get stream index failed";
        return false;
    }
    printf("openInputStream() success\n");


    //get Video resolution
    pAVCodecContext = pAVFormatContext->streams[videoStreamIndex]->codec;
    videoWidth = pAVCodecContext->width;
    videoHeight = pAVCodecContext->height;
    printf("video size : %d * %d\n", videoWidth, videoHeight);
    avpicture_alloc(&pAVPicture, PIX_FMT_RGB24, videoWidth, videoHeight);

    AVCodec *pAVCodec;

    //get decoder
    pAVCodec = avcodec_find_decoder(pAVCodecContext->codec_id);
    pSwsContext = sws_getContext(videoWidth, videoHeight, PIX_FMT_YUV420P, videoWidth, videoHeight, PIX_FMT_RGB24, SWS_BICUBIC, 0, 0, 0);

    //open decoder
    result = avcodec_open2(pAVCodecContext, pAVCodec, NULL);
    if (result < 0)
    {
        cout << "open decoder failed";
        return false;
    }

    cout << "init stream successed" << endl;
    return true;
}


bool FFMPEG::openOutputStream()
{
    int ret;

    int64_t cur_pts_v=0,cur_pts_a=0;
    int frame_index=0, frame_index_audio=0;
    AVRational time_base_q={1, AV_TIME_BASE};

    sprintf(videoSaveName, "./video/%04d%02d%02d%02d%02d%02d.ts", m_year, m_mon, m_day, m_hour, m_min, m_sec);

    //Open output file
    if (!(ofmt->flags & AVFMT_NOFILE))
    {
        ret = avio_open(&ofmt_ctx->pb, videoSaveName, AVIO_FLAG_WRITE);
        if (ret < 0)
        {
            printf( "Could not open output file %s, ret = %d\n", videoSaveName, ret);
            return false;
        }
    }
    //Write file header
    if (ret=avformat_write_header(ofmt_ctx, NULL) < 0)
    {
        printf( "Error occurred when opening output file, ret=%d\n",ret);
        return false;
    }

    //when the recording time reach the defalut, make another recording file
    while(!isTimeReady())
    {
        if (ret=av_read_frame(pAVFormatContext, &pAVPacket) >= 0)
        {
            in_stream  = pAVFormatContext->streams[pAVPacket.stream_index];
            out_stream = ofmt_ctx->streams[pAVPacket.stream_index];

            if(pAVPacket.stream_index==videoStreamIndex)
            {
                if(pAVPacket.pts!=AV_NOPTS_VALUE)
                {
                    //Write PTS
                    AVRational time_base1=in_stream->time_base;
                    if(in_stream->r_frame_rate.num == 0 && in_stream->r_frame_rate.den == 0)
                    {
                        in_stream->r_frame_rate.num = 25;
                        in_stream->r_frame_rate.den = 1;
                    }

                    //Duration between 2 frames (us)
                    int64_t calc_duration=(double)AV_TIME_BASE/av_q2d(in_stream->r_frame_rate);
                    //Parameters
                    pAVPacket.pts=(double)(frame_index*calc_duration)/(double)(av_q2d(time_base1)*AV_TIME_BASE);
                    pAVPacket.dts=pAVPacket.pts;
                    pAVPacket.duration=(double)calc_duration/(double)(av_q2d(time_base1)*AV_TIME_BASE);


//                    printf("vvvvvvvvvvvvvvvvvvvvvvvv\n");
//                    printf("frame_index=%d\n", frame_index);
//                    printf("frame rate num=%d, den=%d\n", in_stream->r_frame_rate.num, in_stream->r_frame_rate.den);
//                    printf("nb_frames=%d\n", in_stream->nb_frames);
//                    printf("av_q2d(time_base1)=%f\n", av_q2d(time_base1));
//                    printf("AV_TIME_BASE=%d\n", AV_TIME_BASE);
//                    printf("calc_duration=%lld\n", calc_duration);
//                    printf("pAVPacket.duration=%d\n", pAVPacket.duration);
//                    printf("frame rate=%f\n", pAVPacket.duration);

                    frame_index++;
                }
                cur_pts_v=pAVPacket.pts;
            }




            if(pAVPacket.stream_index==audioStreamIndex)
            {
                if(pAVPacket.pts!=AV_NOPTS_VALUE)
                {
                    //Write PTS
                    AVRational time_base1=in_stream->time_base;
                    //Duration between 2 frames (us)
                    in_stream->r_frame_rate.num = in_stream->time_base.den;
                    in_stream->r_frame_rate.den = in_stream->time_base.num;
                    int64_t calc_duration=(double)AV_TIME_BASE/av_q2d(in_stream->r_frame_rate);

                    //Parameters
                    pAVPacket.pts=(double)(1024*frame_index_audio*calc_duration)/(double)(av_q2d(time_base1)*AV_TIME_BASE);
                    pAVPacket.dts=pAVPacket.pts;
                    pAVPacket.duration=(double)calc_duration/(double)(av_q2d(time_base1)*AV_TIME_BASE*1024);


//                    printf("aaaaaaaaaaaaaaaaaaaaaaaa\n");
//                    printf("frame_index=%d\n", frame_index);
//                    printf("frame rate num=%d, den=%d\n", in_stream->r_frame_rate.num, in_stream->r_frame_rate.den);
//                    printf("nb_frames=%d\n", in_stream->nb_frames);
//                    printf("av_q2d(time_base1)=%f\n", av_q2d(time_base1));
//                    printf("AV_TIME_BASE=%d\n", AV_TIME_BASE);
//                    printf("calc_duration=%lld\n", calc_duration);
//                    printf("pAVPacket.duration=%d\n", pAVPacket.duration);
//                    printf("frame rate=%f\n", pAVPacket.duration);
//                    printf("pAVPacket.size=%d\n", pAVPacket.size);

                    frame_index_audio++;

                }
                cur_pts_a=pAVPacket.pts;
            }
        }
        else
        {
            printf("ret = %d\n", ret);
        }

        //Convert PTS/DTS
        pAVPacket.pts = av_rescale_q_rnd(pAVPacket.pts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
        pAVPacket.dts = av_rescale_q_rnd(pAVPacket.dts, in_stream->time_base, out_stream->time_base, (AVRounding)(AV_ROUND_NEAR_INF|AV_ROUND_PASS_MINMAX));
        pAVPacket.duration = av_rescale_q(pAVPacket.duration, in_stream->time_base, out_stream->time_base);
        pAVPacket.pos = -1;

//        printf("in_stream->time_base: num=%d, den=%d\n", in_stream->time_base.num, in_stream->time_base.den);
//        printf("out_stream->time_base: num=%d, den=%d\n", out_stream->time_base.num, out_stream->time_base.den);
//        printf("============== pts:%lld, duration:%lld\n\n\n\n", pAVPacket.pts, pAVPacket.duration);


        //Write
        if (ret=av_write_frame(ofmt_ctx, &pAVPacket) < 0) {
                printf( "Error muxing packet, ret=%d\n", ret);
        }

        av_free_packet(&pAVPacket);
    }
        av_write_trailer(ofmt_ctx);


}

void FFMPEG::closeOutputStream()
{
    printf("closeOutputStream()------------------\n");
    avformat_close_input(&pAVFormatContext);
    if (ofmt_ctx && !(ofmt->flags & AVFMT_NOFILE))
            avio_close(ofmt_ctx->pb);
    avformat_free_context(ofmt_ctx);
}


void FFMPEG::getLocalTime()
{
    time_t timer;
    struct tm* t_tm;
    time(&timer);
    t_tm = localtime(&timer);

    m_year = t_tm->tm_year+1900;
    m_mon  = t_tm->tm_mon+1;
    m_day  = t_tm->tm_mday;
    m_hour = t_tm->tm_hour;
    m_min  = t_tm->tm_min;
    m_sec  = t_tm->tm_sec;
    m_time_t = timer;
}

bool FFMPEG::isTimeReady()
{
    getLocalTime();
    if(m_min%2 == 0 && m_sec == 0)
        return true;
    else
        return false;
}


