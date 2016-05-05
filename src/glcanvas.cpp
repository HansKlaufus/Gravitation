#include "glcanvas.h"
#include "maingui.h"
#include "object.h"

#include "wx/wx.h"
#include "wx/glcanvas.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include <vector>

BEGIN_EVENT_TABLE(cGlCanvas, wxGLCanvas)
    EVT_MOTION(cGlCanvas::mouseMoved)
    EVT_LEFT_DOWN(cGlCanvas::onLeftDown)
    EVT_LEFT_UP(cGlCanvas::onLeftReleased)
    EVT_RIGHT_DOWN(cGlCanvas::rightClick)
    EVT_LEAVE_WINDOW(cGlCanvas::mouseLeftWindow)
    EVT_SIZE(cGlCanvas::onSizeEvent)
    EVT_KEY_DOWN(cGlCanvas::keyPressed)
    EVT_KEY_UP(cGlCanvas::keyReleased)
    EVT_MOUSEWHEEL(cGlCanvas::onMouseWheelEvent)
    EVT_PAINT(cGlCanvas::onPaintEvent)
END_EVENT_TABLE()

cGlCanvas::cGlCanvas(wxFrame* parent, int* args) : wxGLCanvas(parent, wxID_ANY, args, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE)
{
	m_parent       = parent;
	m_context      = new wxGLContext(this);

    m_cameraX      = 0;
    m_cameraY      = 0;
    m_cameraZ      = 0;

    m_cameraAngleX = 0;
    m_cameraAngleY = 0;
    m_cameraAngleZ = 0;

    m_upX          = 0;
    m_upY          = 0;
    m_upZ          = 0;

    m_centreX      = 0;
    m_centreY      = 0;
    m_centreZ      = 0;

    m_radius       = 1.0;
    m_initialised  = false;

    m_showBackgroundRaster = true;
    m_showAxisFrame        = true;

    // To avoid flashing on MSW
    SetBackgroundStyle(wxBG_STYLE_CUSTOM);
//    initGL();

}

cGlCanvas::~cGlCanvas()
{
	delete m_context;
}

// some useful events to use
void cGlCanvas::mouseMoved(wxMouseEvent& event)
{
    // Rotate
    static bool  dragging = false;
    static float xOld;
    static float yOld;

    if(event.LeftIsDown()) {
        if(!dragging) {
          dragging = true;
        } else {
          // Rotate
          m_cameraAngleY = m_cameraAngleY + (yOld - event.GetY())/getHeight()*360;
          m_cameraAngleZ = m_cameraAngleZ + (xOld - event.GetX())/getWidth()*360;
          Refresh(false);
        }

        xOld = event.GetX();
        yOld = event.GetY();

    } else if(event.RightIsDown()) {
        if(!dragging) {
          dragging = true;
        } else {
//          m_cameraAngleX = m_cameraAngleX + (xOld - event.GetX())/getWidth()*360;

          //TODO: Panning: Doesn't work..
          m_centreX = m_centreX + m_radius*(xOld - event.GetX())/getWidth();
          m_centreY = m_centreY + m_radius*(yOld - event.GetY())/getHeight();
          Refresh(false);
        }

        xOld = event.GetX();
        yOld = event.GetY();

    } else {
        dragging = false;
    }
}

void cGlCanvas::onMouseWheelEvent(wxMouseEvent& event)
{
    // Zoom in / out
    if (event.GetWheelRotation()>0) {
        m_cameraX *= 1.1;
        m_cameraY *= 1.1;
        m_cameraZ *= 1.1;
    } else {
        m_cameraX /= 1.1;
        m_cameraY /= 1.1;
        m_cameraZ /= 1.1;
    }

    wxString message = wxString::Format(wxT("Camera Position = (%8.3f, %8.3f, %8.3f)"), m_cameraX, m_cameraY, m_cameraZ);
    ((cMainGui*) m_parent)->SetStatusText(message, 0);

    redraw();
}

void cGlCanvas::onLeftDown(wxMouseEvent& event){}
void cGlCanvas::onLeftReleased(wxMouseEvent& event) {}
void cGlCanvas::rightClick(wxMouseEvent& event) {}
void cGlCanvas::mouseLeftWindow(wxMouseEvent& event) {}
void cGlCanvas::keyPressed(wxKeyEvent& event) {}
void cGlCanvas::keyReleased(wxKeyEvent& event) {}

void cGlCanvas::onSizeEvent(wxSizeEvent& evt)
{
//	wxGLCanvas::OnSize(evt);
    Refresh();
}

void cGlCanvas::onPaintEvent( wxPaintEvent& evt )
{
    if(!IsShown()) return;

    wxPaintDC(this); // only to be used in paint events. use wxClientDC to paint outside the paint event
    redraw();
}

void cGlCanvas::initGL(void)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);               // Black Background
    glClearDepth(1.0f);                                 // Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);                            // Enables Depth Testing
    glDepthFunc(GL_LEQUAL);                             // The Type Of Depth Testing To Do
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    // Enable lighting models
    glShadeModel(GL_SMOOTH);                            // Enable shade model
    glEnable(GL_COLOR_MATERIAL);                        // Enable colour tracking
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);  // Use predefined material properties; set by glColor
    glEnable(GL_LIGHTING);                              // Enable lighting model

    // Create light components
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    GLfloat position[] = { 0.0f, 0.0f, 0.0f, 1.0f };

    // Assign created components to GL_LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);     // Define ambient light component
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);     // Define diffuse light component
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);   // Define specular light component
    glLightfv(GL_LIGHT0, GL_POSITION, position);        // Define position of light0
    glEnable(GL_LIGHT0);                                // Enable light0

    m_initialised = true;
}

void cGlCanvas::setProjectionMatrix(int topleft_x, int topleft_y, int bottomrigth_x, int bottomrigth_y)
{
    GLdouble left   = -1.5*m_radius;
    GLdouble right  = +1.5*m_radius;
    GLdouble bottom = -1.5*m_radius;
    GLdouble top    = +1.5*m_radius;

    GLdouble aspect = (GLdouble)(bottomrigth_x - topleft_x) / (GLdouble)(bottomrigth_y - topleft_y);
    if ( aspect < 1.0 ) { // window taller than wide
        bottom /= aspect;
        top /= aspect;
    } else {
        left *= aspect;
        right *= aspect;
    }

    glViewport(topleft_x, topleft_y, bottomrigth_x-topleft_x, bottomrigth_y-topleft_y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if(2*m_radius<20000) {
        gluPerspective(45, aspect, 0.1, 20000);
    } else {
        gluPerspective(45, aspect, 0.1, 2*m_radius);
    }
}

void cGlCanvas::setModelMatrix(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(m_cameraX, m_cameraY, m_cameraZ, -m_centreX, -m_centreY, -m_centreZ, m_upX, m_upY, m_upZ);

//    gluLookAt(m_cameraX, m_cameraY, m_cameraZ, 0, 0, 0, m_upX, m_upY, m_upZ); // Always looks to the origin (0,0,0)
    glRotatef(m_cameraAngleX, 1, 0, 0);
    glRotatef(m_cameraAngleY, 0, 1, 0);
    glRotatef(m_cameraAngleZ, 0, 0, 1);
}

int cGlCanvas::getWidth()
{
    return GetSize().x;
}

int cGlCanvas::getHeight()
{
    return GetSize().y;
}

void cGlCanvas::drawBackgroundRaster(void)
{
    /*
    ** Draw a wire sphere as background raster
    */
    glPushMatrix();
        GLfloat redEmissiveMaterial[] = {1.0, 0.0, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, redEmissiveMaterial);
//        double r = sqrt(m_cameraX*m_cameraX + m_cameraY*m_cameraY + m_cameraZ*m_cameraZ);
        double r = sqrt(m_cameraX*m_cameraX + m_cameraY*m_cameraY + m_cameraZ*m_cameraZ);
        glBegin(GL_LINE_LOOP);
            GLUquadricObj *quadric = gluNewQuadric();
            gluQuadricDrawStyle(quadric, GLU_LINE);
            gluSphere(quadric, r, 36, 36);
            gluDeleteQuadric(quadric);
        glEnd();
    glPopMatrix();
}

void cGlCanvas::drawAxisFrame(void)
{
    /*
    ** Draw an axes frame
    */
    double arrowLength1 = 0.9*m_radius;
    double arrowLength2 = 0.1*m_radius;
    double arrowRadius1 = 0.01*arrowLength1;
    double arrowRadius2 = 0.02*arrowLength1;

    glPushMatrix();
        GLfloat greenEmissiveMaterial[] = {0.0, 1.0, 0.0};
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, greenEmissiveMaterial);
        GLUquadricObj *quadric = gluNewQuadric();

        // Draw Z-axis
        gluQuadricDrawStyle(quadric, GLU_FILL);
        gluCylinder(quadric, arrowRadius1, arrowRadius1, arrowLength1, 20, 20);
        glTranslatef(0, 0, arrowLength1);
        gluCylinder(quadric, arrowRadius2, 0, arrowLength2, 20, 20);
        glTranslatef(0, 0, -arrowLength1);

        // Draw Y-axis
        glRotatef(-90, 1, 0, 0);
        gluQuadricDrawStyle(quadric, GLU_FILL);
        gluCylinder(quadric, arrowRadius1, arrowRadius1, arrowLength1, 20, 20);
        glTranslatef(0, 0, arrowLength1);
        gluCylinder(quadric, arrowRadius2, 0, arrowLength2, 20, 20);
        glTranslatef(0, 0, -arrowLength1);
        glRotatef(90, 1, 0, 0);

        // Draw X-axis
        glRotatef(-90, 0, 1, 0);
        gluQuadricDrawStyle(quadric, GLU_FILL);
        gluCylinder(quadric, arrowRadius1, arrowRadius1, arrowLength1, 20, 20);
        glTranslatef(0, 0, arrowLength1);
        gluCylinder(quadric, arrowRadius2, 0, arrowLength2, 20, 20);
        glTranslatef(0, 0, -arrowLength1);
        glRotatef(90, 0, 1, 0);

        gluDeleteQuadric(quadric);
    glPopMatrix();
}

void cGlCanvas::redraw(void)
{
    initGL();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        SetCurrent(*m_context);
        setProjectionMatrix(0, 0, getWidth(), getHeight());
        setModelMatrix();

        if(m_showBackgroundRaster) drawBackgroundRaster();
        if(m_showAxisFrame) drawAxisFrame();

        if(((cMainGui*)m_parent)->GetNumberObjects()>0)
        {
            std::vector<cObject>           planets  = ((cMainGui*)m_parent)->GetObjects();
            std::vector<cObject>::iterator objectIterator;
            for(objectIterator = planets.begin(); objectIterator != planets.end(); objectIterator++)
            {
                // Draw a planet
                GLdouble radius = objectIterator->GetRadius();
                GLdouble x      = objectIterator->GetX();
                GLdouble y      = objectIterator->GetY();
                GLdouble z      = objectIterator->GetZ();

                glPushMatrix();
                    glColor4f(1, 1, 0, 1);
                    glTranslatef(x, y, z);

                    // Draw a solid sphere
                    glBegin(GL_LINE_LOOP);
                        GLUquadricObj *quadric = gluNewQuadric();
                        gluQuadricDrawStyle(quadric, GLU_FILL);
                        gluSphere(quadric, radius, 20, 20);
                        gluDeleteQuadric(quadric);
                    glEnd();

                    glTranslatef(-x, -y, -z);
                glPopMatrix();
            }
        }
    glPopMatrix();

    glFlush();
    SwapBuffers();
}

void cGlCanvas::redrawDummy(void)
{
    initGL();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
    SetCurrent(*m_context);
    setProjectionMatrix(0, 0, getWidth(), getHeight());
    setModelMatrix();

    if(m_showBackgroundRaster) drawBackgroundRaster();
    if(m_showAxisFrame) drawAxisFrame();

    static int j=0;
    j++;

    int i=0;
    for(int x=-5; x<5; x=x+2)
    {
        for(int y=-5; y<5; y=y+2)
        {
            for (int z=-5; z<5; z=z+2)
            {
                i++;

                // Draw a LED
                glPushMatrix();

                if(j%2==0)
                {
                    if(i%2==0)
                    {
                        GLfloat yellowEmissiveMaterial[] = {1.0, 1.0, 0.0, 1.0};
                        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellowEmissiveMaterial);
                    }
                    else
                    {
                        GLfloat blackDiffusiveMaterial[] = {0.0, 0.0, 0.0, 0.0};
                        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blackDiffusiveMaterial);
                    }
                }
                else
                {
                    if(i%2==0)
                    {
                        GLfloat blackDiffusiveMaterial[] = {0.0, 0.0, 0.0, 0.0};
                        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, blackDiffusiveMaterial);
                    }
                    else
                    {
                        GLfloat yellowEmissiveMaterial[] = {1.0, 1.0, 0.0, 1.0};
                        glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellowEmissiveMaterial);
                    }
                }

                glTranslatef(x, y, z);

                // Draw a solid sphere
                glBegin(GL_LINE_LOOP);
                    GLUquadricObj *quadric = gluNewQuadric();
                    gluQuadricDrawStyle(quadric, GLU_FILL);
                    gluSphere(quadric, 0.1, 20, 20);
                    gluDeleteQuadric(quadric);
                glEnd();

                glPopMatrix();
            }
        }
    }
    glPopMatrix();

    glFlush();
    SwapBuffers();
}

void cGlCanvas::setCameraPosition(double x, double y, double z, double upX, double upY, double upZ)
{
    m_cameraX = x;
    m_cameraY = y;
    m_cameraZ = z;

    m_upX = upX;
    m_upY = upY;
    m_upZ = upZ;
}

void cGlCanvas::setCameraAngle(double angleX, double angleY, double angleZ)
{
    m_cameraAngleX = angleX;
    m_cameraAngleY = angleY;
    m_cameraAngleZ = angleZ;
}
