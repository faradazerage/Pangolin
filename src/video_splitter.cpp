/* This file is part of the Pangolin Project.
 * http://github.com/stevenlovegrove/Pangolin
 *
 * Copyright (c) 2013 Steven Lovegrove
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use,
 * copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#include <pangolin/video_splitter.h>

namespace pangolin
{

VideoSplitter::VideoSplitter(VideoInterface* videoin, const std::vector<ImageRoi>& rois)
    : videoin(videoin)
{
    if(videoin->Streams().size() != 1)
        throw VideoException("VideoSplitter input must have exactly one stream");
    
    const StreamInfo& stmin = videoin->Streams()[0];
    
    for(size_t ir = 0; ir < rois.size(); ++ir)
    {
        const ImageRoi& roi = rois[ir];
        StreamInfo stm(stmin.PixFormat(), roi.w, roi.h, stmin.Pitch(), (unsigned char*)0 + roi.y * stmin.Pitch() + roi.x);
        streams.push_back(stm);
    }
}

VideoSplitter::~VideoSplitter()
{
    delete videoin;
}

size_t VideoSplitter::SizeBytes() const
{
    return videoin->SizeBytes();
}

const std::vector<StreamInfo>& VideoSplitter::Streams() const
{
    return streams;
}

void VideoSplitter::Start()
{
    videoin->Start();
}

void VideoSplitter::Stop()
{
    videoin->Stop();
}

bool VideoSplitter::GrabNext( unsigned char* image, bool wait )
{
    return videoin->GrabNext(image, wait);
}

bool VideoSplitter::GrabNewest( unsigned char* image, bool wait )
{
    return videoin->GrabNewest(image, wait);
}



}
