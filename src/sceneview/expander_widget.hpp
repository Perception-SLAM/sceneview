#ifndef SCENEVIEW_EXPANDER_WIDGET_HPP__
#define SCENEVIEW_EXPANDER_WIDGET_HPP__

#include <QWidget>

class QPushButton;
class QStackedWidget;
class QVBoxLayout;

namespace sceneview {

/**
 * Hides or shows a contained widget.
 */
class ExpanderWidget : public QWidget {
  Q_OBJECT

  public:
    ExpanderWidget(QWidget* parent = nullptr);

    void SetWidget(QWidget* widget);

    QSize sizeHint() const override;

    void SetTitle(const QString& title);
    QString Title() const;

    void SetExpanded(bool val);
    bool Expanded() const { return expanded_; }

  private slots:
    void ToggleExpanded();

  private:
    QPushButton* button_;
    QWidget* widget_;
    QVBoxLayout* layout_;
    bool expanded_;
};

}  // namespace sceneview

#endif  // SCENEVIEW_EXPANDER_WIDGET_HPP__
