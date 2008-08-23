/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkDijkstraImageGeodesicPath.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkDijkstraImageGeodesicPath - Dijkstra algorithm to compute the graph geodesic.
// .SECTION Description
// Takes as input a polyline and an image representing a 2D cost function
// and performs a single source shortest path calculation. 
// Dijkstra's algorithm is used. The implementation is 
// similar to the one described in Introduction to Algorithms (Second Edition)
// by Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and 
// Cliff Stein, published by MIT Press and McGraw-Hill. Some minor 
// enhancement are added though. All vertices are not pushed on the heap
// at start, instead a front set is maintained. The heap is implemented as 
// a binary heap. The output of the filter is a set of lines describing 
// the shortest path from StartVertex to EndVertex.  See parent class
// vtkDijkstraGraphGeodesicPath for the implementation.
//
// .SECTION Caveats
// The input cost image must have only VTK_PIXEL cells: i.e., a 2D image or 
// slice of a 3D volume. A cost function for a gray scale image might 
// be generated by the following pipeline:
// vtkImageData->vtkImageGradientMagnitude->vtkImageShiftScale
// wherein the gradient magnitude image is inverted so that strong edges
// have low cost value.
//
// .SECTION Thanks
// The class was contributed by Dean Inglis.


#ifndef __vtkDijkstraImageGeodesicPath_h
#define __vtkDijkstraImageGeodesicPath_h

#include "vtkDijkstraGraphGeodesicPath.h"

class vtkImageData;

class VTK_GRAPHICS_EXPORT vtkDijkstraImageGeodesicPath :
                           public vtkDijkstraGraphGeodesicPath
{
public:

  // Description:
  // Instantiate the class
  static vtkDijkstraImageGeodesicPath *New();

  // Description:
  // Standard methids for printing and determining type information.
  vtkTypeRevisionMacro( vtkDijkstraImageGeodesicPath, vtkDijkstraGraphGeodesicPath );
  void PrintSelf( ostream& os, vtkIndent indent );
  
  // Description:
  // Use distance between points as an additional cost feature
  vtkSetMacro( UseEdgeLengthsAsWeights, int );
  vtkGetMacro( UseEdgeLengthsAsWeights, int );
  vtkBooleanMacro( UseEdgeLengthsAsWeights, int );

  // Description:
  // Specify the image object which is used as a cost function.
  void SetCostImage( vtkImageData* );
  vtkImageData* GetCostImage();

protected:
  vtkDijkstraImageGeodesicPath();
  ~vtkDijkstraImageGeodesicPath();

  virtual int FillInputPortInformation(int port, vtkInformation *info);
  virtual int RequestData(vtkInformation *, vtkInformationVector **, 
                          vtkInformationVector *);

  // Build a graph description of the mesh
  virtual void BuildAdjacency( vtkDataSet *inData );

  // The cost going from vertex u to v
  // TODO: should be implemented as a user supplied
  // callback function
  virtual double CalculateEdgeCost( vtkDataSet *inData , vtkIdType u, vtkIdType v);

  int UseEdgeLengthsAsWeights;

  double PixelSize;

private:
  vtkDijkstraImageGeodesicPath(const vtkDijkstraImageGeodesicPath&);  // Not implemented.
  void operator=(const vtkDijkstraImageGeodesicPath&);  // Not implemented.

};

#endif

