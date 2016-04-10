/*
  Copyright (C) 2016 Jon Macey

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef ABSTRACTVAO_H_
#define ABSTRACTVAO_H_

#include "Types.h"

namespace ngl
{
//----------------------------------------------------------------------------------------------------------------------
/// @class AbstractVAO "include/AbstractVAO.h"
/// @brief base class for all VAO from the VAOFactory this defines the
/// base class type with simple draw / bind behaviour, the user must allocate the data and
/// do any more complex setup. See SimpleVAO for examples as well as the other ngl examples
/// @author Jonathan Macey
/// @version 1.0
/// @date 6/4/16
//----------------------------------------------------------------------------------------------------------------------

class NGL_DLLEXPORT AbstractVAO
{
  public :
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief dtor usually this will not be called
    //----------------------------------------------------------------------------------------------------------------------
    virtual ~AbstractVAO()=default;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief bind the VAO so it can be used.
    //----------------------------------------------------------------------------------------------------------------------
    void bind();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief unbind the VAO by binding default 0
    //----------------------------------------------------------------------------------------------------------------------
    void unbind();
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this is the draw method for the VAO the user must implement this per VAO data, usually this
    /// will be a call to glDrawArrays type function, VAO must be bound before calling this
    //----------------------------------------------------------------------------------------------------------------------
    virtual void draw()const =0;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief this will clean up the VAO and associated data, it is the users responsibility to do this
    /// usually this will be a call to the various delete buffers gl routines
    //----------------------------------------------------------------------------------------------------------------------
    virtual void removeVAO()=0;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief set the generic vertex attribute pointer data usually this method will do however the user
    /// may occasionally need to override this method.
    /// @param _size the size of the raw data passed (not counting sizeof(GL_FLOAT))
    /// @param _type the data type of the Pointer (eg GL_FLOAT)
    /// @param _stride the step between data values (need *sizeof _type) e.g. 10*sizeof(GLfloat) 0 means tightly packed / contiguous
    /// @param _dataOffset Specifies a pointer to the first component of the first generic vertex attribute in the array.
    /// The initial value is 0. and is calculated as static_cast<Real *>(NULL)  + _dataOffset
    /// @param _normalise specifies whether fixed-point data values should be normalized (GL_TRUE) or converted directly as
    /// fixed-point values (GL_FALSE) when they are accessed.
    //----------------------------------------------------------------------------------------------------------------------
    void setVertexAttributePointer(GLuint _id, GLint _size, GLenum _type, GLsizei _stride, unsigned int _dataOffset, bool _normalise=false );
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the number of indices to draw in the array. It may be that the draw routine can overide this at another time.
    /// @param _s the number of indices to draw (from 0)
    //----------------------------------------------------------------------------------------------------------------------
    void setNumIndices(size_t _s){m_indicesCount=_s;}
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief return the id of the buffer, if there is only 1 buffer just return this
    /// if we have the more than one buffer the sub class manages the id's
    /// @param _buffer index (default to 0 for single buffer VAO's)
    //----------------------------------------------------------------------------------------------------------------------
    virtual GLuint getBufferID(unsigned int _id=0)=0;
  protected :
    //----------------------------------------------------------------------------------------------------------------------
    /// ctor to build the VAO
    /// @param _mode the mode to draw with.
    //----------------------------------------------------------------------------------------------------------------------
    AbstractVAO(GLenum _mode=GL_TRIANGLES) ;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the draw mode
    //----------------------------------------------------------------------------------------------------------------------
    GLenum m_mode=GL_TRIANGLES;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the id of the VAO allocated from OpenGL
    //----------------------------------------------------------------------------------------------------------------------
    GLuint m_id=0;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief debug flag to indicate if the vao is bound.
    //----------------------------------------------------------------------------------------------------------------------
    bool m_bound=false;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief debug flag to indicate if data has been set for the VAO
    //----------------------------------------------------------------------------------------------------------------------
    bool m_allocated=false;
    //----------------------------------------------------------------------------------------------------------------------
    /// @brief the number of indices stored in the VAO.
    //----------------------------------------------------------------------------------------------------------------------
    size_t m_indicesCount=0;
};


} // end namespace

#endif
