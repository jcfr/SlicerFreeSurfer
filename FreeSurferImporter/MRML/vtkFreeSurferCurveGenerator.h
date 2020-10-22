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

#ifndef __vtkFreeSurferCurveGenerator_h
#define __vtkFreeSurferCurveGenerator_h

// Slicer includes
#include <vtkCurveGenerator.h>

// vtk includes
#include <vtkSetGet.h>
#include <vtkSmartPointer.h>

// export
#include "vtkSlicerFreeSurferImporterModuleMRMLExport.h"

/// Filter that generates curves between points of an input polydata
class VTK_SLICER_FREESURFERIMPORTER_MODULE_MRML_EXPORT vtkFreeSurferCurveGenerator : public vtkCurveGenerator
{
public:
  vtkTypeMacro(vtkFreeSurferCurveGenerator, vtkCurveGenerator);
  static vtkFreeSurferCurveGenerator* New();

  void PrintSelf(ostream& os, vtkIndent indent) override;

protected:

protected:
  vtkFreeSurferCurveGenerator();
  ~vtkFreeSurferCurveGenerator() override;
  vtkFreeSurferCurveGenerator(const vtkFreeSurferCurveGenerator&) = delete;
  void operator=(const vtkFreeSurferCurveGenerator&) = delete;
};

#endif
