#include <opencv2/opencv.hpp>
#include <chrono>

int main(int argc, char** argv) {
    cv::VideoCapture cap(0);  // 打开默认摄像头
    
    if (!cap.isOpened()) {
        std::cerr << "无法打开摄像头" << std::endl;
        return -1;
    }
    
    // 获取视频帧率
    int frame_width = cap.get(cv::CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(cv::CAP_PROP_FRAME_HEIGHT);
    
    int frame_rate = 20;  // 你可以设置需要的帧率
    int five_minutes_in_sec = 5 * 60;
    int frames_per_segment = five_minutes_in_sec * frame_rate;

    int segment_counter = 0;

    // 循环不断抓取帧
    while(true) {
        cv::Mat frame;
        cap >> frame;  // 抓取一帧
        
        if (frame.empty())
            break;
        
        // 如果是一个新的视频段落，创建一个新的VideoWriter
        if (segment_counter % frames_per_segment == 0) {
            std::string output_file = "output" + std::to_string(segment_counter / frames_per_segment) + ".avi";

            // 定义视频编码器和输出文件
            cv::VideoWriter video(output_file, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 
                                  frame_rate, cv::Size(frame_width,frame_height));
        }
        
        // 写入当前帧
        video.write(frame);

        // 如果已经写入足够的帧数，关闭当前的VideoWriter
        if (segment_counter % frames_per_segment == frames_per_segment - 1) {
            video.release();
        }

        segment_counter++;
    }
    
    cap.release();
    cv::destroyAllWindows();
    
    return 0;
}
