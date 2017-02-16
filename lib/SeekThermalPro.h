/*
 *  Seek thermal pro interface
 *  Author: Maarten Vandersteegen
 */

#ifndef SEEK_THERMAL_PRO_H
#define SEEK_THERMAL_PRO_H

#include <opencv2/opencv.hpp>
#include "SeekCam.h"

#define THERMAL_PRO_WIDTH       320
#define THERMAL_PRO_HEIGHT      240
#define THERMAL_PRO_RAW_WIDTH   342
#define THERMAL_PRO_RAW_HEIGHT  260
#define THERMAL_PRO_RAW_SIZE    (THERMAL_PRO_RAW_WIDTH * THERMAL_PRO_RAW_HEIGHT)

namespace LibSeek {

class SeekThermalPro: public SeekCam
{
public:
    SeekThermalPro();
    ~SeekThermalPro();

    /*
     *  Initialize the camera
     *  Returns true on success
     */
    virtual bool open();

    /*
     *  De-initialise the camera
     */
    virtual void close();

    /*
     *  Check if device is open
     */
    virtual bool isOpened();

    /*
     *  Grab a frame
     *  Returns true on success
     */
    virtual bool grab();

    /*
     *  Retrieve the last grabbed frame
     *  Returns true on success
     */
    virtual bool retrieve(cv::Mat& dst);

private:
    const int m_offset;

    bool m_is_opened;
    SeekDevice m_dev;
    uint16_t m_raw_data[THERMAL_PRO_RAW_SIZE];
    cv::Mat m_raw_frame;
    cv::Mat m_frame;
    cv::Mat m_flat_field_calibration_frame;
    cv::Mat m_dead_pixel_mask;
    std::vector<cv::Point> m_dead_pixel_list;

    bool init_cam();
    bool get_frame();
    int frame_id();
    int frame_counter();
    void create_dead_pixel_list();
    void apply_dead_pixel_filter();
    uint16_t calc_mean_value(cv::Point p, int right_border, int lower_border);
};

} /* LibSeek */

#endif /* SEEK_THERMAL_PRO_H */