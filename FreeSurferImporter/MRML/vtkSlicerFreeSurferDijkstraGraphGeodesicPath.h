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

#ifndef __vtkSlicerFreeSurferDijkstraGraphGeodesicPath_h
#define __vtkSlicerFreeSurferDijkstraGraphGeodesicPath_h

// Markups MRML includes
#include <vtkSlicerDijkstraGraphGeodesicPath.h>

// export
#include "vtkSlicerFreeSurferImporterModuleMRMLExport.h"

/// Filter that generates curves between points of an input polydata
class VTK_SLICER_FREESURFERIMPORTER_MODULE_MRML_EXPORT vtkSlicerFreeSurferDijkstraGraphGeodesicPath : public vtkSlicerDijkstraGraphGeodesicPath
{
public:
  vtkTypeMacro(vtkSlicerFreeSurferDijkstraGraphGeodesicPath, vtkDijkstraGraphGeodesicPath);
  static vtkSlicerFreeSurferDijkstraGraphGeodesicPath* New();
  void PrintSelf(ostream& os, vtkIndent indent) override;

protected:
  /// The fixed cost going from vertex u to v.
  /// Reimplemented to provide additonal cost function types.
  /// \sa SetCostFunctionType()
  double CalculateStaticEdgeCost(vtkDataSet* inData, vtkIdType u, vtkIdType v) override;

  /// The fixed cost going from vertex u to v.
  /// Reimplemented to provide additonal cost function types.
  /// \sa SetCostFunctionType()
  double CalculateDynamicEdgeCost(vtkDataSet* inData, vtkIdType u, vtkIdType v) override;
 
  vtkSetMacro(DistanceEnabled, bool);
  vtkGetMacro(DistanceEnabled, bool);
  vtkBooleanMacro(DistanceEnabled, bool);

  vtkSetMacro(CurvEnabled, bool);
  vtkGetMacro(CurvEnabled, bool);
  vtkBooleanMacro(CurvEnabled, bool);

  vtkSetMacro(SulcEnabled, bool);
  vtkGetMacro(SulcEnabled, bool);
  vtkBooleanMacro(SulcEnabled, bool);

  vtkSetMacro(DistanceCurvEnabled, bool);
  vtkGetMacro(DistanceCurvEnabled, bool);
  vtkBooleanMacro(DistanceCurvEnabled, bool);

  vtkSetMacro(DistanceSulcEnabled, bool);
  vtkGetMacro(DistanceSulcEnabled, bool);
  vtkBooleanMacro(DistanceSulcEnabled, bool);
  
  vtkSetMacro(CurvSulcEnabled, bool);
  vtkGetMacro(CurvSulcEnabled, bool);
  vtkBooleanMacro(CurvSulcEnabled, bool);

  vtkSetMacro(DistanceCurvSulcEnabled, bool);
  vtkGetMacro(DistanceCurvSulcEnabled, bool);
  vtkBooleanMacro(DistanceCurvSulcEnabled, bool);

  vtkSetMacro(DirectionEnabled, bool);
  vtkGetMacro(DirectionEnabled, bool);
  vtkBooleanMacro(DirectionEnabled, bool);

protected:
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath();
  ~vtkSlicerFreeSurferDijkstraGraphGeodesicPath() override;
  vtkSlicerFreeSurferDijkstraGraphGeodesicPath(const vtkSlicerFreeSurferDijkstraGraphGeodesicPath&) = delete;
  void operator=(const vtkSlicerFreeSurferDijkstraGraphGeodesicPath&) = delete;

  bool DistanceEnabled;
  bool CurvEnabled;
  bool SulcEnabled;
  bool DistanceCurvEnabled;
  bool DistanceSulcEnabled;
  bool CurvSulcEnabled;
  bool DistanceCurvSulcEnabled;
  bool DirectionEnabled;
  double AntiGreedyThreshold;
};

#endif
