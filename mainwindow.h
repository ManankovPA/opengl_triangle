#pragma once
#include <QOpenGLWidget>
#include <QElapsedTimer>
#include <vector>
#include <string>

struct vertex
{
    GLfloat x;
    GLfloat y;
    GLfloat z;
};

struct main_window : QOpenGLWidget
{
    main_window(QWidget* parent = nullptr);

private:
    double angle = 0.0;
    QElapsedTimer time;

    std::vector<vertex>figure;

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    void upload_modelview_matrix();
    void initialize_figure();
    void select_figure_side();
    void draw_figure_side(std::vector<size_t>const& side);
};
