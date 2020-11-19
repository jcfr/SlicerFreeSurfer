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
  Care Ontario, OpenAnatomy, and Brigham and Women's Hospital through NIH grant R01MH112748.

==============================================================================*/

// FreeSurfer includes
#include "vtkFreeSurferCurveGenerator.h"

#include <vtkSlicerFreeSurferDijkstraGraphGeodesicPath.h>

#include <vtkMRMLNode.h>

//------------------------------------------------------------------------------
vtkCurveGeneratorNewMacro(vtkFreeSurferCurveGenerator);

//------------------------------------------------------------------------------
vtkFreeSurferCurveGenerator::vtkFreeSurferCurveGenerator()
{
  this->SurfacePathFilter = vtkSmartPointer<vtkSlicerFreeSurferDijkstraGraphGeodesicPath>::New();
  this->SurfacePathFilter->StopWhenEndReachedOn();
}

//------------------------------------------------------------------------------
vtkFreeSurferCurveGenerator::~vtkFreeSurferCurveGenerator() = default;

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::PrintSelf(std::ostream & os, vtkIndent indent)
{
  Superclass::PrintSelf(os, indent);
  vtkMRMLPrintBeginMacro(os, indent);
  vtkMRMLPrintFloatMacro(DistanceWeight);
  vtkMRMLPrintFloatMacro(CurvatureWeight);
  vtkMRMLPrintFloatMacro(SulcalHeightWeight);
  vtkMRMLPrintFloatMacro(DistanceCurvatureWeight);
  vtkMRMLPrintFloatMacro(DistanceSulcalHeightWeight);
  vtkMRMLPrintFloatMacro(CurvatureSulcalHeightWeight);
  vtkMRMLPrintFloatMacro(DistanceCurvatureSulcalHeightWeight);
  vtkMRMLPrintFloatMacro(DirectionWeight);
  vtkMRMLPrintFloatMacro(CurvaturePenalty);
  vtkMRMLPrintFloatMacro(SulcalHeightPenalty);
  vtkMRMLPrintFloatMacro(DistanceCurvaturePenalty);
  vtkMRMLPrintFloatMacro(DistanceSulcalHeightPenalty);
  vtkMRMLPrintFloatMacro(CurvatureSulcalHeightPenalty);
  vtkMRMLPrintFloatMacro(DistanceCurvatureSulcalHeightPenalty);
  vtkMRMLPrintEndMacro();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::ReadXMLAttributes(const char** atts)
{
  Superclass::ReadXMLAttributes(atts);
  vtkMRMLReadXMLBeginMacro(atts);
  vtkMRMLReadXMLFloatMacro(distanceWeight, DistanceWeight);
  vtkMRMLReadXMLFloatMacro(curvatureWeight, CurvatureWeight);
  vtkMRMLReadXMLFloatMacro(sulcalHeightWeight, SulcalHeightWeight);
  vtkMRMLReadXMLFloatMacro(distanceCurvatureWeight, DistanceCurvatureWeight);
  vtkMRMLReadXMLFloatMacro(distanceSulcalHeightWeight, DistanceSulcalHeightWeight);
  vtkMRMLReadXMLFloatMacro(curvatureSulcalHeightWeight, CurvatureSulcalHeightWeight);
  vtkMRMLReadXMLFloatMacro(distanceCurvatureSulcalHeightWeight, DistanceCurvatureSulcalHeightWeight);
  vtkMRMLReadXMLFloatMacro(directionWeight, DirectionWeight);
  vtkMRMLReadXMLFloatMacro(curvaturePenalty, CurvaturePenalty);
  vtkMRMLReadXMLFloatMacro(sulcalHeightPenalty, SulcalHeightPenalty);
  vtkMRMLReadXMLFloatMacro(distanceCurvaturePenalty, DistanceCurvaturePenalty);
  vtkMRMLReadXMLFloatMacro(distanceSulcalHeightPenalty, DistanceSulcalHeightPenalty);
  vtkMRMLReadXMLFloatMacro(curvatureSulcalHeightPenalty, CurvatureSulcalHeightPenalty);
  vtkMRMLReadXMLFloatMacro(distanceCurvatureSulcalHeightPenalty, DistanceCurvatureSulcalHeightPenalty);
  vtkMRMLReadXMLEndMacro(atts)
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::WriteXML(ostream & of, int indent)
{
  Superclass::WriteXML(of, indent);
  vtkMRMLWriteXMLBeginMacro(of, indent);
  vtkMRMLWriteXMLFloatMacro(distanceWeight, DistanceWeight);
  vtkMRMLWriteXMLFloatMacro(curvatureWeight, CurvatureWeight);
  vtkMRMLWriteXMLFloatMacro(sulcalHeightWeight, SulcalHeightWeight);
  vtkMRMLWriteXMLFloatMacro(distanceCurvatureWeight, DistanceCurvatureWeight);
  vtkMRMLWriteXMLFloatMacro(distanceSulcalHeightWeight, DistanceSulcalHeightWeight);
  vtkMRMLWriteXMLFloatMacro(curvatureSulcalHeightWeight, CurvatureSulcalHeightWeight);
  vtkMRMLWriteXMLFloatMacro(distanceCurvatureSulcalHeightWeight, DistanceCurvatureSulcalHeightWeight);
  vtkMRMLWriteXMLFloatMacro(directionWeight, DirectionWeight);
  vtkMRMLWriteXMLFloatMacro(curvaturePenalty, CurvaturePenalty);
  vtkMRMLWriteXMLFloatMacro(sulcalHeightPenalty, SulcalHeightPenalty);
  vtkMRMLWriteXMLFloatMacro(distanceCurvaturePenalty, DistanceCurvaturePenalty);
  vtkMRMLWriteXMLFloatMacro(distanceSulcalHeightPenalty, DistanceSulcalHeightPenalty);
  vtkMRMLWriteXMLFloatMacro(curvatureSulcalHeightPenalty, CurvatureSulcalHeightPenalty);
  vtkMRMLWriteXMLFloatMacro(distanceCurvatureSulcalHeightPenalty, DistanceCurvatureSulcalHeightPenalty);
  vtkMRMLWriteXMLEndMacro();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetDistanceWeight(double weight)
{
  if (weight == this->GetDistanceWeight())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetDistanceWeight(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetCurvatureWeight(double weight)
{
  if (weight == this->GetCurvatureWeight())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetCurvatureWeight(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetSulcalHeightWeight(double weight)
{
  if (weight == this->GetSulcalHeightWeight())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetSulcalHeightWeight(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetDistanceCurvatureWeight(double weight)
{
  if (weight == this->GetDistanceCurvatureWeight())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetDistanceCurvatureWeight(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetDistanceSulcalHeightWeight(double weight)
{
  if (weight == this->GetDistanceSulcalHeightWeight())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetDistanceSulcalHeightWeight(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetCurvatureSulcalHeightWeight(double weight)
{
  if (weight == this->GetCurvatureSulcalHeightWeight())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetCurvatureSulcalHeightWeight(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetDistanceCurvatureSulcalHeightWeight(double weight)
{
  if (weight == this->GetDistanceCurvatureSulcalHeightWeight())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetDistanceCurvatureSulcalHeightWeight(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetDirectionWeight(double weight)
{
  if (weight == this->GetDirectionWeight())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetDirectionWeight(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetCurvaturePenalty(double weight)
{
  if (weight == this->GetCurvaturePenalty())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetCurvaturePenalty(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetSulcalHeightPenalty(double weight)
{
  if (weight == this->GetSulcalHeightPenalty())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetSulcalHeightPenalty(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetDistanceCurvaturePenalty(double weight)
{
  if (weight == this->GetDistanceCurvaturePenalty())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetDistanceCurvaturePenalty(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetDistanceSulcalHeightPenalty(double weight)
{
  if (weight == this->GetDistanceSulcalHeightPenalty())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetDistanceSulcalHeightPenalty(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetCurvatureSulcalHeightPenalty(double weight)
{
  if (weight == this->GetCurvatureSulcalHeightPenalty())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetCurvatureSulcalHeightPenalty(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
void vtkFreeSurferCurveGenerator::SetDistanceCurvatureSulcalHeightPenalty(double weight)
{
  if (weight == this->GetDistanceCurvatureSulcalHeightPenalty())
  {
    return;
  }
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->SetDistanceCurvatureSulcalHeightPenalty(weight);
  this->Modified();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetDistanceWeight()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetCurvatureWeight()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetSulcalHeightWeight()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetDistanceCurvatureWeight()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetDistanceSulcalHeightWeight()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetCurvatureSulcalHeightWeight()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetDistanceCurvatureSulcalHeightWeight()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetDirectionWeight()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetCurvaturePenalty()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetSulcalHeightPenalty()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetDistanceCurvaturePenalty()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetDistanceSulcalHeightPenalty()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetCurvatureSulcalHeightPenalty()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}

//------------------------------------------------------------------------------
double vtkFreeSurferCurveGenerator::GetDistanceCurvatureSulcalHeightPenalty()
{
  return vtkSlicerFreeSurferDijkstraGraphGeodesicPath::SafeDownCast(this->SurfacePathFilter)->GetDistanceWeight();
}
