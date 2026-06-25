/*
 * Copyright (C) 2025 s-trinh
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of  MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>
#include <visp3/core/vpImage.h>
#include <visp3/core/vpIoTools.h>
#include <visp3/core/vpCannyEdgeDetection.h>
#include <visp3/core/vpImageFilter.h>
#include <visp3/io/vpImageIo.h>

#ifdef ENABLE_VISP_NAMESPACE
using namespace VISP_NAMESPACE_NAME;
#endif

int main(int, const char **)
{
  std::srand(0);

  std::string input = "MEF_img_0000.png";
  vpImage<unsigned char> I_gray;
  vpImageIo::read(I_gray, input);

  int gaussianKernelSize = 3;
  float gaussianStdev = 1.0f;
  int apertureSize = 3;
  vpImageFilter::vpCannyFilteringAndGradientType filteringType = vpImageFilter::CANNY_GBLUR_SOBEL_FILTERING;
  // Canny parameters
  float lowerThresh = -1.;
  float upperThresh = -1.;
  float lowerThreshRatio = 0.6f;
  float upperThreshRatio = 0.8f;

  for (int i = 0; i < 3; i++)
  {
    vpCannyEdgeDetection cannyDetector(gaussianKernelSize, gaussianStdev, apertureSize,
                                lowerThresh, upperThresh, lowerThreshRatio, upperThreshRatio,
                                filteringType, false, -1);

    vpImage<unsigned char> I_canny = cannyDetector.detect(I_gray);
    const double canny_mean = I_canny.getMeanValue();
    std::cout << "canny_mean=" << canny_mean << std::endl;

    std::ostringstream oss;
    oss << "I_canny_" << i << ".png";
    vpImageIo::write(I_canny, oss.str());
  }

  return EXIT_SUCCESS;
}
