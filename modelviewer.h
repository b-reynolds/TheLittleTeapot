#ifndef MODEL_VIEWER_H
#define MODEL_VIEWER_H

#include "model.h"
#include <QGLWidget>
#include <QColor>

/* Forward declaration */
class Model;

/**
 * @brief ModelViewer class (inherits from QGLWidget)
 */
class ModelViewer : public QGLWidget
{
    Q_OBJECT

public:

    /* Render modes enumeration */
    enum RenderMode { ePointCloud, eWireframe };

    /* Default constructor, initialises variables to default values */
    explicit ModelViewer(QWidget* parent = 0);

    /* Sets the ModelViewer's Model */
    void setModel(const Model& model);

    /* Returns a reference to the ModelViewer's model */
    Model& model();

    /* Sets the ModelViewer's background colour */
    void setBackgroundColour(const QColor& colour);

    /* Returns the ModelViewer's background colour */
    QColor backgroundColour() const;

    /* Sets the ModelViewer's foreground colour */
    void setForegroundColour(const QColor& colour);

    /* Returns the ModelViewer's foreground colour */
    QColor foregroundColour() const;

    /* Sets the ModelViewer's point size */
    void setPointSize(const GLfloat& pointSize);

    /* Sets the ModelViewer's zoom amount */
    void setZoomAmount(const GLfloat& zoomAmount);

    /* Returns the ModelViewer's zoom amount */
    GLfloat zoomAmount() const;

    /* Sets the ModelViewer's render mode */
    void setRenderMode(const RenderMode& renderMode);

    /* Returns the ModelViewer's render mode */
    RenderMode renderMode();

protected:

    /* Initialises OpenGL (called once, before the first ModelViewer::paintGL call) */
    virtual void initializeGL() override;

    /* Paints the ModelViewer (called whenever the Widget needs to be painted) */
    virtual void paintGL() override;

    /* Handles resizing of the ModelViewer Widget */
    virtual void resizeGL(int width, int height) override;

private:

    Model mModel;

    const QColor cBackgroundColourDefault = QColor(4.001f, 27.999f, 49.001f, 255.0f);
    const QColor cForegroundColourDefault = QColor(160.0f, 189.0f, 255.0f, 255.0f);
    const GLfloat cPointSizeDefault = 1.0f;
    const GLdouble cZoomAmountDefault = 1.0;
    const RenderMode cRenderModeDefault = ePointCloud;
    const GLdouble cNear = 1.0;
    const GLdouble cFar = 15.0;

    QColor mBackgroundColour;
    QColor mForegroundColour;

    GLfloat mPointSize;

    GLdouble mZoomAmount;

    RenderMode mRenderMode;


};

#endif // MODEL_VIEWER_H
