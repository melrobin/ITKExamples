/*=========================================================================
 *
 *  Copyright Insight Software Consortium
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkAdaptiveHistogramEqualizationImageFilter.h"
#include "itkImageFileReader.h"
#include "itkImageFileWriter.h"

int main( int argc, char *argv[] )
{
  if( argc < 6 )
    {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << argv[0]
      << " inputImageFile outputImageFile alpha beta radius" << std::endl;
    return EXIT_FAILURE;
    }

  const unsigned int Dimension = 2;

  typedef unsigned char                       PixelType;
  typedef itk::Image< PixelType, Dimension >  ImageType;

  typedef itk::ImageFileReader< ImageType > FileReaderType;
  FileReaderType::Pointer reader = FileReaderType::New();
  reader->SetFileName( argv[1] );

  typedef itk::AdaptiveHistogramEqualizationImageFilter< ImageType > AdaptiveHistogramEqualizationImageFilterType;
  AdaptiveHistogramEqualizationImageFilterType::Pointer adaptiveHistogramEqualizationImageFilter = AdaptiveHistogramEqualizationImageFilterType::New();

  float alpha = atof( argv[3] );
  adaptiveHistogramEqualizationImageFilter->SetAlpha( alpha );

  float beta = atof( argv[4] );
  adaptiveHistogramEqualizationImageFilter->SetBeta( beta );

  int radiusSize = atoi( argv[5] );
  AdaptiveHistogramEqualizationImageFilterType::ImageSizeType radius;
  radius.Fill( radiusSize );
  adaptiveHistogramEqualizationImageFilter->SetRadius( radius );

  adaptiveHistogramEqualizationImageFilter->SetInput( reader->GetOutput() );

  adaptiveHistogramEqualizationImageFilter->Update();

  typedef itk::ImageFileWriter< ImageType > WriterType;
  WriterType::Pointer writer = WriterType::New();
  writer->SetFileName( argv[2] );
  writer->SetInput( adaptiveHistogramEqualizationImageFilter->GetOutput() );

  writer->Update();

  return EXIT_SUCCESS;
}
