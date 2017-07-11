/*! Utilities for time sampling for visual effects.
 */

#ifndef VFX_TIME_UTILS_H
#define VFX_TIME_UTILS_H

#include <cmath>    // modf, ceil
#include <iostream> // cout, cerr, endl
#include <vector>   // vector
#include <string>   // string

namespace vfxtime {

    /*! @typedef List of Sub-Frames */
    typedef std::vector<double> SubFrameList;
    typedef SubFrameList::iterator SubFrameListIt;
    typedef SubFrameList::const_iterator SubFrameListCIt;

    typedef std::pair<double, SubFrameList> FramePair;
    /*! @typedef List of Frames */
    typedef std::vector<FramePair> FrameList;
    typedef FrameList::iterator FrameListIt;
    typedef FrameList::const_iterator FrameListCIt;

    /*! Calculate the safe floating-point time value in Autodesk Maya.
     *
     * Takes the ticks and fps into account when calculating float numbers in Maya.
     *
     * See these links:
     * https://knowledge.autodesk.com/support/maya/learn-explore/caas/CloudHelp/cloudhelp/2015/ENU/Maya/files/How-Maya-counts-time-htm.html
     * http://help.autodesk.com/view/MAYAUL/2017/ENU/?guid=GUID-A9F91D81-3149-47AF-9E37-83A89242D870
     *
     * @param time [in] Floating point time value.
     * @param time [in] Time value to operate on.
     * @param fps [in] Frames Per-Second of the time value in Maya.
     * @param fps [in] Frames per-second (FPS) for the given time number.
     *
     * @return Maya floating-point time value, rounded based on Maya "ticks".
     */
    static inline
    double getSafeMayaTime(
            double time,
            unsigned int fps
    ) {
        int ticksPerSecond = 6000;  // Maya 2016 and below.
        int ticksPerFrame = ticksPerSecond / fps;
        int ticks = int(time * ticksPerFrame);
        double t = ceil(ticks);
        double intpart = 0;
        double mod = modf(ticks, &intpart);
        if (mod < 0.5) {
            t = floor(ticks);
        }
        t = t / ticksPerFrame;
        return t;
    }

    /*! Get time samples.
     *
     * @param start [in]
     * @param end [in]
     * @param shutterSamples [in]
     * @param shutterAngle [in]
     * @param outFrames [out]
     * @return true or false based on success.
     */
    static inline
    bool getTimeSamples(double start,
                        double end,
                        unsigned int shutterSamples,
                        double shutterAngle,
                        FrameList &outFrames) {
        outFrames.clear();

        // Create list of frames to render.
        for (double i = start; i <= end; ++i) {
            // std::cout << "i=" << i << std::endl;
            SubFrameList subframes;
            double angle = 0.0;
            if (shutterSamples > 1 && shutterAngle > 0.01) {
                angle = -(shutterAngle / 360.0) * 0.5;
                for (int j = 0; j < shutterSamples; ++j) {
                    // std::cout << "shutter j=" << j << ", angle=" << angle << std::endl;
                    double timeAngle = angle;
                    subframes.push_back(i + timeAngle);
                    angle += (shutterAngle / 360.0) * (1.0 / (float) (shutterSamples - 1));
                }
            } else {
                // std::cout << "shutter j=" << 0 << ", angle=" << angle << std::endl;
                subframes.push_back(i);
            }
            FramePair p = FramePair(i, subframes);
            outFrames.push_back(p);
        }

//        // Loop over all frames.
//        double currentTime = 0;
//        FrameListIt frame_it = outFrames.begin();
//        for (; frame_it != outFrames.end(); ++frame_it) {
//            double frame = frame_it->first;
//            std::cout << "frame=" << frame << std::endl;
//            SubFrameList subframes = frame_it->second;
//            SubFrameListIt subframe_it = subframes.begin();
//            for (; subframe_it != subframes.end(); ++subframe_it) {
//                currentTime = *subframe_it;
//                std::cout << "subframe=" << currentTime << std::endl;
//            }
//        }

        return true;
    }

    // TODO: Write a function to return a list of (maya valid?) times.

}

#endif // VFX_TIME_UTILS_H
