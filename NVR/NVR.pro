#-------------------------------------------------
#
# Project created by QtCreator 2019-01-10T17:46:10
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = NVRServer
CONFIG   += console
CONFIG   -= app_bundle
#CONFIG   += arm

TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++0x -fpermissive

arm{
LIBS += -L/home/hzmct/res/lib_ffmpeg-2.1.8_arm/lib/ -lavformat -lavdevice -lavfilter -lavcodec -lavutil -lswresample -lswscale -lpostproc \
        -L/home/hzmct/res/lib_sdl-1.2_arm/lib/ -lSDL \
        -L/home/hzmct/res/lib_x264_arm/lib/ -lx264
}else{
LIBS += -L/home/hzmct/res/lib_ffmpeg-2.1.8-add-pcm/lib/ -lavformat -lavdevice -lavfilter -lavcodec -lavutil -lswresample -lswscale
}

INCLUDEPATH += \
    live/groupsock/include/ \
    live/UsageEnvironment/include/ \
    live/BasicUsageEnvironment/include/ \
    live/groupsock/include/ \
    live/liveMedia/include \
    ffmpeg/include

SOURCES += main.cpp \
    network/CCommonThread.cpp \
    live/BasicUsageEnvironment/DelayQueue.cpp \
    live/BasicUsageEnvironment/BasicUsageEnvironment0.cpp \
    live/BasicUsageEnvironment/BasicUsageEnvironment.cpp \
    live/BasicUsageEnvironment/BasicTaskScheduler0.cpp \
    live/BasicUsageEnvironment/BasicTaskScheduler.cpp \
    live/BasicUsageEnvironment/BasicHashTable.cpp \
    live/groupsock/IOHandlers.cpp \
    live/groupsock/NetAddress.cpp \
    live/groupsock/GroupsockHelper.cpp \
    live/groupsock/GroupEId.cpp \
    live/groupsock/NetInterface.cpp \
    live/groupsock/Groupsock.cpp \
    live/groupsock/inet.c \
    live/UsageEnvironment/HashTable.cpp \
    live/UsageEnvironment/strDup.cpp \
    live/UsageEnvironment/UsageEnvironment.cpp \
    live/liveMedia/H261VideoRTPSource.cpp \
    live/liveMedia/OggDemuxedTrack.cpp \
    live/liveMedia/MPEG4LATMAudioRTPSource.cpp \
    live/liveMedia/MP3FileSource.cpp \
    live/liveMedia/ADTSAudioFileServerMediaSubsession.cpp \
    live/liveMedia/MediaSource.cpp \
    live/liveMedia/MP3InternalsHuffmanTable.cpp \
    live/liveMedia/MPEG2TransportStreamIndexFile.cpp \
    live/liveMedia/H265VideoRTPSource.cpp \
    live/liveMedia/MatroskaFileServerDemux.cpp \
    live/liveMedia/MP3Transcoder.cpp \
    live/liveMedia/AC3AudioRTPSink.cpp \
    live/liveMedia/MPEG1or2AudioRTPSource.cpp \
    live/liveMedia/AC3AudioFileServerMediaSubsession.cpp \
    live/liveMedia/MP3StreamState.cpp \
    live/liveMedia/H264VideoStreamFramer.cpp \
    live/liveMedia/AMRAudioRTPSource.cpp \
    live/liveMedia/MPEG1or2VideoRTPSink.cpp \
    live/liveMedia/H263plusVideoStreamParser.cpp \
    live/liveMedia/RTSPServerSupportingHTTPStreaming.cpp \
    live/liveMedia/FramedSource.cpp \
    live/liveMedia/TextRTPSink.cpp \
    live/liveMedia/H265VideoFileSink.cpp \
    live/liveMedia/MP3InternalsHuffman.cpp \
    live/liveMedia/ProxyServerMediaSession.cpp \
    live/liveMedia/MPEG2TransportStreamMultiplexor.cpp \
    live/liveMedia/MPEG1or2AudioStreamFramer.cpp \
    live/liveMedia/MPEG4ESVideoRTPSource.cpp \
    live/liveMedia/FramedFileSource.cpp \
    live/liveMedia/AMRAudioFileSink.cpp \
    live/liveMedia/FileServerMediaSubsession.cpp \
    live/liveMedia/PassiveServerMediaSubsession.cpp \
    live/liveMedia/VorbisAudioRTPSource.cpp \
    live/liveMedia/H265VideoStreamFramer.cpp \
    live/liveMedia/MP3AudioMatroskaFileServerMediaSubsession.cpp \
    live/liveMedia/H263plusVideoStreamFramer.cpp \
    live/liveMedia/H264VideoFileServerMediaSubsession.cpp \
    live/liveMedia/BitVector.cpp \
    live/liveMedia/H264or5VideoStreamDiscreteFramer.cpp \
    live/liveMedia/TheoraVideoRTPSink.cpp \
    live/liveMedia/ByteStreamMemoryBufferSource.cpp \
    live/liveMedia/VorbisAudioRTPSink.cpp \
    live/liveMedia/MatroskaDemuxedTrack.cpp \
    live/liveMedia/MPEG2TransportStreamFromESSource.cpp \
    live/liveMedia/OggFileParser.cpp \
    live/liveMedia/FramedFilter.cpp \
    live/liveMedia/H265VideoRTPSink.cpp \
    live/liveMedia/DeviceSource.cpp \
    live/liveMedia/MPEG2TransportStreamFromPESSource.cpp \
    live/liveMedia/SimpleRTPSink.cpp \
    live/liveMedia/H264or5VideoRTPSink.cpp \
    live/liveMedia/FileSink.cpp \
    live/liveMedia/TheoraVideoRTPSource.cpp \
    live/liveMedia/VP8VideoRTPSource.cpp \
    live/liveMedia/RTCP.cpp \
    live/liveMedia/MPEG4GenericRTPSink.cpp \
    live/liveMedia/RTSPRegisterSender.cpp \
    live/liveMedia/RTPInterface.cpp \
    live/liveMedia/JPEGVideoRTPSource.cpp \
    live/liveMedia/MP3ADUTranscoder.cpp \
    live/liveMedia/AMRAudioRTPSink.cpp \
    live/liveMedia/RTPSource.cpp \
    live/liveMedia/MPEG2TransportStreamTrickModeFilter.cpp \
    live/liveMedia/T140TextRTPSink.cpp \
    live/liveMedia/MPEGVideoStreamParser.cpp \
    live/liveMedia/RTSPClient.cpp \
    live/liveMedia/MediaSink.cpp \
    live/liveMedia/SIPClient.cpp \
    live/liveMedia/OggFileServerDemux.cpp \
    live/liveMedia/QuickTimeGenericRTPSource.cpp \
    live/liveMedia/MP3ADU.cpp \
    live/liveMedia/MP3ADURTPSource.cpp \
    live/liveMedia/MatroskaFileParser.cpp \
    live/liveMedia/VideoRTPSink.cpp \
    live/liveMedia/MPEG1or2DemuxedServerMediaSubsession.cpp \
    live/liveMedia/MP3ADUinterleaving.cpp \
    live/liveMedia/H264VideoRTPSink.cpp \
    live/liveMedia/MPEG2IndexFromTransportStream.cpp \
    live/liveMedia/MPEGVideoStreamFramer.cpp \
    live/liveMedia/H264VideoRTPSource.cpp \
    live/liveMedia/MPEG1or2VideoRTPSource.cpp \
    live/liveMedia/OggFile.cpp \
    live/liveMedia/H264or5VideoStreamFramer.cpp \
    live/liveMedia/MP3ADURTPSink.cpp \
    live/liveMedia/MPEG4VideoFileServerMediaSubsession.cpp \
    live/liveMedia/JPEGVideoSource.cpp \
    live/liveMedia/AMRAudioSource.cpp \
    live/liveMedia/ServerMediaSession.cpp \
    live/liveMedia/Media.cpp \
    live/liveMedia/OggFileSink.cpp \
    live/liveMedia/GSMAudioRTPSink.cpp \
    live/liveMedia/SimpleRTPSource.cpp \
    live/liveMedia/AMRAudioFileSource.cpp \
    live/liveMedia/MP3Internals.cpp \
    live/liveMedia/MPEG1or2VideoStreamFramer.cpp \
    live/liveMedia/QCELPAudioRTPSource.cpp \
    live/liveMedia/MPEG2TransportFileServerMediaSubsession.cpp \
    live/liveMedia/MPEG2TransportStreamAccumulator.cpp \
    live/liveMedia/MPEG1or2FileServerDemux.cpp \
    live/liveMedia/EBMLNumber.cpp \
    live/liveMedia/RTPSink.cpp \
    live/liveMedia/RawVideoRTPSink.cpp \
    live/liveMedia/MPEG4LATMAudioRTPSink.cpp \
    live/liveMedia/MediaSession.cpp \
    live/liveMedia/MPEG4VideoStreamFramer.cpp \
    live/liveMedia/BasicUDPSource.cpp \
    live/liveMedia/MultiFramedRTPSink.cpp \
    live/liveMedia/H264VideoFileSink.cpp \
    live/liveMedia/DVVideoRTPSource.cpp \
    live/liveMedia/QuickTimeFileSink.cpp \
    live/liveMedia/MultiFramedRTPSource.cpp \
    live/liveMedia/VP9VideoRTPSink.cpp \
    live/liveMedia/MPEG1or2DemuxedElementaryStream.cpp \
    live/liveMedia/RawVideoRTPSource.cpp \
    live/liveMedia/H264or5VideoFileSink.cpp \
    live/liveMedia/WAVAudioFileServerMediaSubsession.cpp \
    live/liveMedia/MPEG1or2VideoFileServerMediaSubsession.cpp \
    live/liveMedia/AC3AudioStreamFramer.cpp \
    live/liveMedia/RTSPCommon.cpp \
    live/liveMedia/StreamReplicator.cpp \
    live/liveMedia/MatroskaFileServerMediaSubsession.cpp \
    live/liveMedia/MPEG4ESVideoRTPSink.cpp \
    live/liveMedia/H264VideoStreamDiscreteFramer.cpp \
    live/liveMedia/Locale.cpp \
    live/liveMedia/JPEGVideoRTPSink.cpp \
    live/liveMedia/TCPStreamSink.cpp \
    live/liveMedia/OggFileServerMediaSubsession.cpp \
    live/liveMedia/ByteStreamMultiFileSource.cpp \
    live/liveMedia/uLawAudioFilter.cpp \
    live/liveMedia/RTSPServer.cpp \
    live/liveMedia/GenericMediaServer.cpp \
    live/liveMedia/ourMD5.cpp \
    live/liveMedia/MP3AudioFileServerMediaSubsession.cpp \
    live/liveMedia/AudioInputDevice.cpp \
    live/liveMedia/MPEG4GenericRTPSource.cpp \
    live/liveMedia/H263plusVideoFileServerMediaSubsession.cpp \
    live/liveMedia/VP8VideoRTPSink.cpp \
    live/liveMedia/BasicUDPSink.cpp \
    live/liveMedia/StreamParser.cpp \
    live/liveMedia/MP3ADUdescriptor.cpp \
    live/liveMedia/MPEG4VideoStreamDiscreteFramer.cpp \
    live/liveMedia/H263plusVideoRTPSource.cpp \
    live/liveMedia/H265VideoStreamDiscreteFramer.cpp \
    live/liveMedia/AMRAudioFileServerMediaSubsession.cpp \
    live/liveMedia/MPEG1or2AudioRTPSink.cpp \
    live/liveMedia/MPEG2TransportUDPServerMediaSubsession.cpp \
    live/liveMedia/Base64.cpp \
    live/liveMedia/AVIFileSink.cpp \
    live/liveMedia/DVVideoStreamFramer.cpp \
    live/liveMedia/WAVAudioFileSource.cpp \
    live/liveMedia/OutputFile.cpp \
    live/liveMedia/DigestAuthentication.cpp \
    live/liveMedia/RTSPServerRegister.cpp \
    live/liveMedia/ByteStreamFileSource.cpp \
    live/liveMedia/VP9VideoRTPSource.cpp \
    live/liveMedia/MPEG1or2VideoStreamDiscreteFramer.cpp \
    live/liveMedia/MPEG1or2Demux.cpp \
    live/liveMedia/AC3AudioRTPSource.cpp \
    live/liveMedia/InputFile.cpp \
    live/liveMedia/DVVideoRTPSink.cpp \
    live/liveMedia/DVVideoFileServerMediaSubsession.cpp \
    live/liveMedia/MPEG2TransportStreamFramer.cpp \
    live/liveMedia/MatroskaFile.cpp \
    live/liveMedia/H263plusVideoRTPSink.cpp \
    live/liveMedia/OnDemandServerMediaSubsession.cpp \
    live/liveMedia/ADTSAudioFileSource.cpp \
    live/liveMedia/H265VideoFileServerMediaSubsession.cpp \
    live/liveMedia/AudioRTPSink.cpp \
    live/liveMedia/rtcp_from_spec.c \
    live/proxyServer/DynamicRTSPServer.cpp \
    ffmpeg/ffmpeg.cpp \
    live/proxy.cpp

HEADERS += \
    network/CCommonThread.h \
    network/ctypedef.h \
    live/proxyServer/version.hh \
    live/proxyServer/DynamicRTSPServer.hh \
    ffmpeg/ffmpeg.h \
    live/proxy.h
