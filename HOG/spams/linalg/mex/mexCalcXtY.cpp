
/* Software SPAMS v2.1 - Copyright 2009-2011 Julien Mairal 
 *
 * This file is part of SPAMS.
 *
 * SPAMS is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * SPAMS is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with SPAMS.  If not, see <http://www.gnu.org/licenses/>.
 */

/*!
 * \file
 *                toolbox Linalg 
 *
 *                by Julien Mairal
 *                julien.mairal@inria.fr
 *
 *                File mexCalcXtY.h
 * \brief mex-file, function mexCalcXtY.h 
 * Usage: XtY = mexCalcXtY(X,Y); */

#include <mex.h>
#include <mexutils.h>

template <typename T>
   inline void callFunction(mxArray* plhs[], const mxArray*prhs[]) {
      if (!mexCheckType<T>(prhs[0])) 
         mexErrMsgTxt("type of argument 1 is not consistent");
      if (mxIsSparse(prhs[0])) 
         mexErrMsgTxt("argument 1 should be full");
      if (!mexCheckType<T>(prhs[1])) 
         mexErrMsgTxt("type of argument 2 is not consistent");
      if (mxIsSparse(prhs[1])) 
         mexErrMsgTxt("argument 2 should be full");

      T* prX = reinterpret_cast<T*>(mxGetPr(prhs[0]));
      const mwSize* dimsX=mxGetDimensions(prhs[0]);
      long n=static_cast<long>(dimsX[0]);
      long M=static_cast<long>(dimsX[1]);
      T* prY = reinterpret_cast<T*>(mxGetPr(prhs[1]));
      const mwSize* dimsY=mxGetDimensions(prhs[1]);
      long nY=static_cast<long>(dimsY[0]);
      long MY=static_cast<long>(dimsY[1]);
      if (n != nY)
         mexErrMsgTxt("argument sizes are not consistent");

      plhs[0]=createMatrix<T>(M,MY);
      T* prXY=reinterpret_cast<T*>(mxGetPr(plhs[0]));

      Matrix<T> X(prX,n,M);
      Matrix<T> Y(prY,nY,MY);
      Matrix<T> XtY(prXY,M,MY);
      X.mult(Y,XtY,true,false);
}

void mexFunction(int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]) {
   if (nrhs != 2)
      mexErrMsgTxt("Bad number of inputs arguments");

   if (nlhs != 1) 
      mexErrMsgTxt("Bad number of output arguments");

   if (mxGetClassID(prhs[0]) == mxDOUBLE_CLASS) {
      callFunction<double>(plhs,prhs);
   } else {
      callFunction<float>(plhs,prhs);
   }
}


