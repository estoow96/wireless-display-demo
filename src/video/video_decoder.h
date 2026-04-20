#ifndef VIDEO_DECODER_H
#define VIDEO_DECODER_H

typedef struct {
    int width;
    int height;
    int bitrate;
    // Add other fields as needed
} VideoDecoder;

void initialize_decoder(VideoDecoder *decoder, int width, int height, int bitrate);
void decode_video(VideoDecoder *decoder, const char *video_data);
void release_decoder(VideoDecoder *decoder);

#endif // VIDEO_DECODER_H
