#ifndef FFMPEG_H
#define FFMPEG_H
#include "network/CCommonThread.h"
extern "C"
{
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavfilter/avfilter.h>
    #include <libswscale/swscale.h>
    #include <libavutil/frame.h>
}

class FFMPEG:public ICommonThread{
public:
    FFMPEG();
    ~FFMPEG();

    bool initService();
    bool openInputStream();
    bool openOutputStream();
    void closeOutputStream();
    bool isTimeReady();
    void getLocalTime();


private:
    CCommonThread m_commonThread;
    void ThreadProc();
    bool IsRun();

    char m_channel;
    int videoStreamIndex;
    int audioStreamIndex;
    int videoindex_out;
    int audioindex_out;
    int videoWidth;
    int videoHeight;
    int timeSpan;           //make a record file every timeSpan minites
    int m_year, m_mon, m_day, m_hour, m_min, m_sec, m_time_t;
    FILE *fp;
    char videoSavePath[100];
    char videoSaveName[1024];
    AVPicture  pAVPicture;
    AVFormatContext *pAVFormatContext;
    AVCodecContext *pAVCodecContext;
    AVFrame *pAVFrame;
    SwsContext * pSwsContext;
    AVPacket pAVPacket;

    AVOutputFormat *ofmt;
    AVFormatContext *ofmt_ctx;
    AVStream *in_stream, *out_stream;
};

#endif // FFMPEG_H
