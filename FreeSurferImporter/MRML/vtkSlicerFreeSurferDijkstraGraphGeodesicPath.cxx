/*==============================================================================

  Copyright (c) Laboratory for Percutaneous Surgery (PerkLab)
  Queen's University, Kingston, ON, Canada. All Rights Reserved.

  See COPYRIGHT.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Kyle Sunderland, PerkLab, Queen's University
  and was supported through CANARIE's Research Software Program, Cancer
  Care Ontario, OpenAnatomy, and Brigham and Women’s Hospital through NIH grant R01MH112748.

==============================================================================*/

// Markups MRML includes
#include "vtkSlicerFreeSurferDijkstraGraphGeodesicPath.h"

// VTK includes
#include <vtkDoubleArray.h>
#include <vtkFloatArray.h>
#include <vtkPointData.h>
#include <vtkInformation.h>
#include <vtkInformationVector.h>

//------------------------------------------------------------------------------
vtkStandardNewMacro(vtkSlicerFreeSurferDijkstraGraphGeodesicPath);

//------------------------------------------------------------------------------
vtkSlicerFreeSurferDijkstraGraphGeodesicPath::vtkSlicerFreeSurferDijkstraGraphGeodesicPath()
{
  this->DistanceEnabled   = true;
  this->CurvEnabled   = false;
  this->SulcEnabled   = false;
  this->DistanceCurvEnabled  = false;
  this->DistanceSulcEnabled  = false;
  this->CurvSulcEnabled  = false;
  this->DistanceCurvSulcEnabled = false;
  this->DirectionEnabled   = false;
  this->AntiGreedyThreshold = 5.0;
}

//------------------------------------------------------------------------------
vtkSlicerFreeSurferDijkstraGraphGeodesicPath::~vtkSlicerFreeSurferDijkstraGraphGeodesicPath() = default;

//------------------------------------------------------------------------------
void vtkSlicerFreeSurferDijkstraGraphGeodesicPath::PrintSelf(std::ostream &os, vtkIndent indent)
{
  Superclass::PrintSelf(os, indent);
}

//------------------------------------------------------------------------------
double vtkSlicerFreeSurferDijkstraGraphGeodesicPath::CalculateStaticEdgeCost(
  vtkDataSet* inData, vtkIdType u, vtkIdType v)
{
  return 0.0;
  //double p1[3];
  //inData->GetPoint(u, p1);
  //double p2[3];
  //inData->GetPoint(v, p2);
  //double w = sqrt(vtkMath::Distance2BetweenPoints(p1, p2));
}

//------------------------------------------------------------------------------
double vtkSlicerFreeSurferDijkstraGraphGeodesicPath::CalculateDynamicEdgeCost(
  vtkDataSet* inData, vtkIdType u, vtkIdType v)
{
  if (!inData)
    {
    return 0.0;
    }

  double p1[3];
  inData->GetPoint(u, p1);
  double p2[3];
  inData->GetPoint(v, p2);

  double weight = 0.0;

  double distance = sqrt(vtkMath::Distance2BetweenPoints(p1, p2)); // d
  double curv = 0.0;
  double sulc = 0.0;


  double antiGreedyWeightFactor = 1.0;;

  vtkPointData* pointData = inData->GetPointData();
  if (pointData)
  {
    vtkDoubleArray* curvArray = vtkDoubleArray::SafeDownCast(pointData->GetArray("curv"));
    if (curvArray)
    {
      curv = curvArray->GetValue(v);
      if (curv >= 0)
        {
        antiGreedyWeightFactor = 10.0;
        }
      curv = curvArray->GetValueRange()[0] - curv;
    }
    vtkDoubleArray* sulcArray = vtkDoubleArray::SafeDownCast(pointData->GetArray("sulc"));
    if (sulcArray)
    {
      sulc = sulcArray->GetValue(v);
    }
  }

  if (this->DistanceEnabled)
  {
    weight += distance;
  }

  if (this->CurvEnabled)
  {
    weight += curv * antiGreedyWeightFactor;
  }

  if (this->SulcEnabled)
  {
    weight += sulc * antiGreedyWeightFactor;
  }

  if (this->DistanceSulcEnabled)
  {
    weight += distance * sulc * antiGreedyWeightFactor;
  }

  if (this->DistanceCurvEnabled)
  {
    weight += distance * curv * antiGreedyWeightFactor;
  }

  if (this->DistanceCurvSulcEnabled)
  {
    weight += distance * curv * sulc;
  }

  if (this->DirectionEnabled)
  {
    double endVertex[3] = { 0.0 };
    inData->GetPoint(this->EndVertex, endVertex);

    double edgeDirection[3] = { 0.0 };
    vtkMath::Subtract(p2, p1, edgeDirection);
    vtkMath::Normalize(edgeDirection);

    double directionToEnd[3] = { 0.0 };
    vtkMath::Subtract(p2, p1, directionToEnd);
    vtkMath::Normalize(directionToEnd);

    weight += 1.0 - vtkMath::Dot(edgeDirection, directionToEnd);
  }

  return weight;
}



