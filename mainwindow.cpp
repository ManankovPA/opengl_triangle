#include "mainwindow.h"
#include "GL/glu.h"

main_window::main_window(QWidget* parent)
    : QOpenGLWidget(parent)
{}

void main_window::draw_figure_side(std::vector<size_t>const &side)
{
    glVertex3f(figure[side[0]].x, figure[side[0]].y, figure[side[0]].z);
    glVertex3f(figure[side[1]].x, figure[side[1]].y, figure[side[1]].z);
    glVertex3f(figure[side[2]].x, figure[side[2]].y, figure[side[2]].z);


    glVertex3f(figure[side[2]].x, figure[side[2]].y, figure[side[2]].z);
    glVertex3f(figure[side[3]].x, figure[side[3]].y, figure[side[3]].z);
    glVertex3f(figure[side[1]].x, figure[side[1]].y, figure[side[1]].z);
}

void main_window::select_figure_side()
{
    std::vector<size_t> up_side;
    std::vector<size_t> down_side;
    std::vector<size_t> left_side;
    std::vector<size_t> right_side;
    std::vector<size_t> close_side;
    std::vector<size_t> far_side;

    for(size_t i = 0; i < figure.size(); ++i)
    {
        if(figure[i].y == 1.)
            up_side.push_back(i);
        if(figure[i].y == 0.)
            down_side.push_back(i);
        if(figure[i].x == 0.)
            left_side.push_back(i);
        if(figure[i].x == 1)
            right_side.push_back(i);
        if(figure[i].z == 1.)
            close_side.push_back(i);
        if(figure[i].z == 0.)
            far_side.push_back(i);
    }

    glColor3f(0.0, 0.0, 1.0);
    draw_figure_side(up_side);
    glColor3f(0.0, 1.0, 0.0);
    draw_figure_side(down_side);
    glColor3f(0.0, 1.0, 1.0);
    draw_figure_side(left_side);
    glColor3f(1.0, 0.0, 0.0);
    draw_figure_side(right_side);
    glColor3f(1.0, 0.0, 1.0);
    draw_figure_side(close_side);
    glColor3f(1.0, 1.0, 1.0);
    draw_figure_side(far_side);
}

void main_window::initialize_figure()
{
    figure.push_back({0.0, 0.0, 0.0});
    figure.push_back({0.0, 0.0, 1.0});
    figure.push_back({0.0, 1.0, 0.0});
    figure.push_back({0.0, 1.0, 1.0});
    figure.push_back({1.0, 0.0, 0.0});
    figure.push_back({1.0, 0.0, 1.0});
    figure.push_back({1.0, 1.0, 0.0});
    figure.push_back({1.0, 1.0, 1.0});
}

void main_window::initializeGL()
{
    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);
    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //glEnable(GL_COLOR_MATERIAL);
    initialize_figure();
    upload_modelview_matrix();

    time.start();
}

void main_window::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)w/h, 0.01, 100.0);  
}

void main_window::paintGL()
{    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    angle += time.restart() * 0.1;
    upload_modelview_matrix();

    glBegin(GL_TRIANGLES);
    select_figure_side();

    glEnd();
    update();
}

void main_window::upload_modelview_matrix ()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 5, 0, 0, 0, 0, 1, 0);
    glRotated(angle, 1, 1, 1);
}
