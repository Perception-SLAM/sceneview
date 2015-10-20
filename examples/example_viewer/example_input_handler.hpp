#ifndef VIS_EXAMPLES_INPUT_HANDLER_HPP__
#define VIS_EXAMPLES_INPUT_HANDLER_HPP__

#include <sceneview/sceneview.hpp>

class QTimer;

namespace vis_examples {

class ExampleInputHandler : public QObject, public sceneview::InputHandler {
  Q_OBJECT

  public:
    ExampleInputHandler(sceneview::Viewport* viewport,
        QObject* parent = nullptr);

    QString Name() const override { return "Example controls"; }

    /**
     * Called when the OpenGL context is ready for use.
     */
    void InitializeGL() override;

    /**
     * Called when the OpenGL context is shutting down (usually, right before
     * destruction).
     */
    void ShutdownGL() override;

    /**
     * Called when the input handler is activated and given control.
     */
    void Activated() override;

    /**
     * Called when the input handler is deactivated.
     */
    void Deactivated() override;

    void MousePressEvent(QMouseEvent* event) override;

    void MouseMoveEvent(QMouseEvent* event) override;

    void MouseReleaseEvent(QMouseEvent* event) override;

    void WheelEvent(QWheelEvent* event) override;

    void KeyPressEvent(QKeyEvent* event) override;

    void KeyReleaseEvent(QKeyEvent* event) override;

    QWidget* GetWidget() override;

  private:
    void Update();

    sceneview::Viewport* viewport_;
    sceneview::MeshNode* shape_;

    QVector3D shape_dir_;
    QVector3D shape_pos_;
    double shape_speed_;
    QTimer* timer_;
};

}  // namespace vis_examples

#endif  // VIS_EXAMPLES_INPUT_HANDLER_HPP__
