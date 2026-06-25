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
  std::string input = "MEF_img_0000.png";
  vpImage<unsigned char> I_gray;
  vpImageIo::read(I_gray, input);

  const int gaussianKernelSize = 3;
  const float gaussianStdev = 1.0f;
  const int apertureSize = 3;
  const vpImageFilter::vpCannyFilteringAndGradientType filteringType = vpImageFilter::CANNY_GBLUR_SOBEL_FILTERING;
  // Canny parameters
  const float lowerThresh = -1.0f;
  const float upperThresh = -1.0f;
  const float lowerThreshRatio = 0.6f;
  const float upperThreshRatio = 0.8f;
  const bool storeEdgePoints = false;
  const int nbCannyThread = 1;

  const int nb_data = 8;
  const int nb_threads = 8;
  std::vector<vpImage<unsigned char>> I_canny_vec(nb_data);

  #pragma omp parallel for num_threads(nb_threads)
  for (int i = 0; i < nb_data; i++) {
    vpCannyEdgeDetection cannyDetector(gaussianKernelSize, gaussianStdev, apertureSize,
                                lowerThresh, upperThresh, lowerThreshRatio, upperThreshRatio,
                                filteringType, storeEdgePoints, nbCannyThread);

    I_canny_vec[i] = cannyDetector.detect(I_gray);
  }

  for (int i = 0; i < nb_data; i++) {
    const double canny_mean = I_canny_vec[i].getMeanValue();
    std::cout << i << ") canny_mean=" << canny_mean << std::endl;
  }

  return EXIT_SUCCESS;
}
