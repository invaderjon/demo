// model_object.h
//
// An object that has a model.
//
#ifndef DEMO_MODEL_OBJECT_H
#define DEMO_MODEL_OBJECT_H

#include "demo/object/object.h"
#include "demo/render/model.h"

namespace demo
{

namespace obj
{

class ModelObject : public Object
{
  private:
    // MEMBERS
    /**
     * The 3D model.
     */
    rndr::ModelPtr _model;

  public:
    // CONSTRUCTORS
    /**
     * Construct a blank ModelObject.
     */
    ModelObject();

    /**
     * Construct an object with the given model.
     * @param model The model.
     */
    ModelObject( rndr::ModelPtr model );

    /**
     * Construct a copy of another ModelObject.
     * @param other The other ModelObject.
     */
    ModelObject( const ModelObject& other );

    /**
     * Destruct the ModelObject.
     */
    ~ModelObject();

    // OPERATORS
    /**
     * Assign this as a copy of another ModelObject.
     * @param other The other ModelObject.
     * @return This.
     */
    ModelObject& operator=( const ModelObject& other );

    // ACCESSOR FUNCTIONS
    /**
     * Check if the object is renderable.
     * @return Is it renderable?
     */
    bool isRenderable() const override;

    // MUTATOR FUNCTIONS
    /**
     * Set the model.
     * @param model The model.
     */
    void setModel( const rndr::ModelPtr model );

    // MEMBER FUNCTIONS
    /**
     * Render the object.
     * @param shader The shader to use during rendering.
     */
    void render( const rndr::Shader& shader ) override;
};

// CONSTRUCTORS
inline
ModelObject::ModelObject() : _model()
{
}

inline
ModelObject::ModelObject( rndr::ModelPtr model ) : _model( model )
{
}

inline
ModelObject::ModelObject( const ModelObject& other )
        : Object( other ), _model( other._model )
{
}

inline
ModelObject::~ModelObject()
{
}

// OPERATORS
inline
ModelObject& ModelObject::operator=( const ModelObject& other )
{
    Object::operator=( other );

    _model = other._model;

    return *this;
}

// ACCESSOR FUNCTIONS
inline
bool ModelObject::isRenderable() const
{
    return _model->isLoaded();
}

// MUTATOR FUNCTIONS
inline
void ModelObject::setModel( rndr::ModelPtr model )
{
    _model = model;
}

// MEMBER FUNCTIONS
inline
void ModelObject::render( const rndr::Shader& shader )
{
    _model->render( shader );
}

} // End nspc obj

} // End nspc demo

#endif // DEMO_MODEL_OBJECT_H
