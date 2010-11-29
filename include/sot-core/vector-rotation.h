/*
 * Copyright 2010,
 * François Bleibel,
 * Olivier Stasse,
 *
 * CNRS/AIST
 *
 * This file is part of sot-core.
 * sot-core is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of
 * the License, or (at your option) any later version.
 * sot-core is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.  You should
 * have received a copy of the GNU Lesser General Public License along
 * with sot-core.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __SOT_VECTOR_ROTATION_H__
#define __SOT_VECTOR_ROTATION_H__

/* Matrix */
#include <jrl/mal/boost.hh>
namespace ml = maal::boost;

/* --- SOT --- */
#include <sot-core/matrix-rotation.h>
#include <sot-core/sot-core-api.h>

/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */
/* --------------------------------------------------------------------- */

namespace sot {

class SOT_CORE_EXPORT VectorRotation
: public ml::Vector
{
 public:

  VectorRotation( void ) : ml::Vector(3) { fill(0.); }
  virtual ~VectorRotation( void ) { }

  virtual VectorRotation& fromMatrix( const MatrixRotation& rot ) = 0;
  virtual MatrixRotation& toMatrix( MatrixRotation& rot ) const = 0;
};

} // namespace sot

#endif /* #ifndef __SOT_VECTOR_ROTATION_H__ */



