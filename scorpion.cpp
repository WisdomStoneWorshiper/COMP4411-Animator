#pragma warning (disable : 4305)
#pragma warning (disable : 4244)
#pragma warning(disable : 4786)
#include "scorpion.h"
#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.141592653589793238462643383279502
#endif
#define cos45 0.7071067812
#define cos30 0.8660
#define cos75 0.2528
#define sin75 0.9695
#define leg_back -0.75
#define leg_mid -2
#define leg_front -3.25

#define l_init "F-F-F-F-F-F-F-F"
#define F_transform "F---F+F+F+F+F+F+F---F"
#define G_transform "GG"
#define l_angle 45
#define l_length 10.0f

#define num_tail_seg 5

enum ScorpionModelControls
{
	XPOS, YPOS, ZPOS, L_CLAW, LF_CLAW, R_CLAW, RF_CLAW, TAIL, L_LEG, R_LEG, ENABLE_L, L_SIZE, LIGHT_X, LIGHT_Y, LIGHT_Z, LIGHT_INTENSITY, FOG_DENSITY, METABALLS, NUMCONTROLS
};

// Colors
#define COLOR_RED		1.0f, 0.0f, 0.0f
#define COLOR_GREEN		0.0f, 1.0f, 0.0f
#define COLOR_BLUE		0.0f, 0.0f, 1.0f

// We'll be getting the instance of the application a lot; 
// might as well have it as a macro.
#define VAL(x) (ModelerApplication::Instance()->GetControlValue(x))


ModelerView* createScorpionModel(int x, int y, int w, int h, char* label)
{
	
	return new ScorpionModel(x, y, w, h, label);
}

ScorpionModel::ScorpionModel(int x, int y, int w, int h, char* label)
	: ModelerView(x, y, w, h, label) { 
	mb = new Metaballs(num_tail_seg);
	Vec3d start(-35, 35, 35),  end(35, -35, -35),  step(2, -2, -2);
	
	mc = new MarchingCube(start, end, step);
	mc->setMetaBalls(mb, 0.3f);
	//mc->setStepValue(2);

}


void ScorpionModel::draw()
{
	// This call takes care of a lot of the nasty projection 
	// matrix stuff.  Unless you want to fudge directly with the 
	// projection matrix, don't bother with this ...
	ModelerView::draw();
	GLfloat lightPos[] = { (float)VAL(LIGHT_X), (float)VAL(LIGHT_Y), (float)VAL(LIGHT_Z), 0 };
	GLfloat lightIntensity[] = { (float)VAL(LIGHT_INTENSITY), (float)VAL(LIGHT_INTENSITY), (float)VAL(LIGHT_INTENSITY), 1};
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightIntensity);

	glEnable(GL_FOG);
	glFogf(GL_FOG_DENSITY, VAL(FOG_DENSITY)/50);

	// draw the floor
	/*setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(0.49,0.83,0.1);*/
	if (VAL(ENABLE_L)) {
		glPushMatrix();
		glTranslated(-5, 0, 12.5);
		houdini_lsystem();
		//drawBox(10, 0.01f, 10);
		glPopMatrix();
	}

	glDisable(GL_LIGHTING);
glPushMatrix();
setAmbientColor(.5f, .5f, .5f);
setDiffuseColor(1, 0.718, 0.773);
glTranslated(-5, 0, -5);
//glColor3f(COLOR_GREEN);
glScalef(10,0,10);
drawBox(1, 1, 1);
glPopMatrix();
glEnable(GL_LIGHTING);

	// main body
	setAmbientColor(.1f, .1f, .1f);
	setDiffuseColor(0.43,0.30,0.1);
	glPushMatrix();
	glTranslated(VAL(XPOS), VAL(YPOS), VAL(ZPOS));
	glTranslated(0, 1.5, -2.5);
	glScaled(1.5, 0.75, 2);

		//draw torso
		glPushMatrix();
		drawCylinder(0.25, .55, .60);
		glTranslated(0, 0, 0.25);
		drawCylinder(0.25, .60, .65);
		glTranslated(0, 0, 0.25);
		drawCylinder(0.25, .65, .75);
		glTranslated(0, 0, 0.25);
		drawCylinder(0.25, .75, .75);
		glTranslated(0, 0, 0.25);
		drawCylinder(0.25, .75, .75);
		glTranslated(0, 0, 0.25);
		drawCylinder(0.25, .75, .65);
		glTranslated(0, 0, 0.25);
		drawCylinder(0.25, .65, .60);
		glTranslated(0, 0, 0.25);
		drawCylinder(0.25, .60, .55);

		//face
		drawSphere(0.60);
		setDiffuseColor(0,0,0);
		glTranslated(0.075, 0.5, 0.5);
		drawSphere(0.05);
		glTranslated(-0.15, 0, 0);
		drawSphere(0.05);
		setDiffuseColor(COLOR_GREEN);
		glPopMatrix();

		
			//left arm
			glPushMatrix();
			//left back arm
			setDiffuseColor(0.56, 0.39, 0.12);
			glTranslated(-0.35, 0, 2.15);
			glScaled(1 / 1.5, 1 / 0.75, 0.5);
			glRotated(VAL(L_CLAW), 0.0, 1.0, 0.0);
			drawCylinder(1, .15, .15);

			//left middle arm
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glTranslated(-.75, 0, cos45);
			drawCylinder(1, .15, .20);
			//left front arm
			glPushMatrix();
			glRotated(45, 0.0, 1.0, 0.0);
			glRotated(90, 1.0, 0.0, 0.0);
			glTranslated(-cos45, 1.3, 0);
			glScaled(2, 5, 2);
			drawSphere(0.15);
			glRotated(-90, 1.0, 0.0, 0.0);
			glRotated(45, 0.0, 1.0, 0.0);
			setDiffuseColor(0.28, 0.15, 0.03);
			
				//left claw 1
				glPushMatrix();
				glRotated(-VAL(LF_CLAW), 1.0, 0.0, 0.0);
				glTranslated(0, 0.075, 0.05);
				glScaled(1 / 2.0, 1 / 3.0, 1 / 2.0);
				drawCylinder(0.65, .13, .04);
				glPopMatrix();

				// left claw 2
				glPushMatrix();
				glRotated(VAL(LF_CLAW), 1.0, 0.0, 0.0);
				glTranslated(0, -0.075, 0.05);
				glScaled(1 / 2.0, 1 / 3.0, 1 / 2.0);
				drawCylinder(0.65, .13, .04);
				glPopMatrix();
			

			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
			//end left arm

			//right arm
			glPushMatrix();
			//right back arm
			setDiffuseColor(0.56, 0.39, 0.12);
			glTranslated(0.35, 0, 2.15);
			glScaled(1 / 1.5, 1 / 0.75, 0.5);
			glRotated(VAL(R_CLAW), 0.0, 1.0, 0.0);
			drawCylinder(1, .15, .15);

			//right middle arm
			glPushMatrix();
			glRotated(-45, 0.0, 1.0, 0.0);
			glTranslated(.73, 0, cos45);
			drawCylinder(1, .15, .20);
			//right front arm
			glPushMatrix();
			glRotated(-45, 0.0, 1.0, 0.0);
			glRotated(90, 1.0, 0.0, 0.0);
			glTranslated(cos45, 1.3, 0);
			glScaled(2, 5, 2);
			drawSphere(0.15);
			glRotated(-90, 1.0, 0.0, 0.0);
			glRotated(-45, 0.0, 1.0, 0.0);
			setDiffuseColor(0.28, 0.15, 0.03);
			
				//right claw 1
				glPushMatrix();
				glRotated(-VAL(RF_CLAW), 1.0, 0.0, 0.0);
				glTranslated(0, 0.075, 0.05);
				glScaled(1 / 2.0, 1 / 3.0, 1 / 2.0);
				drawCylinder(0.65, .13, .04);
				glPopMatrix();

				// right claw 2
				glPushMatrix();
				glRotated(VAL(RF_CLAW), 1.0, 0.0, 0.0);
				glTranslated(0, -0.075, 0.05);
				glScaled(1 / 2.0, 1 / 3.0, 1 / 2.0);
				drawCylinder(0.65, .13, .04);
				glPopMatrix();
			

			glPopMatrix();
			glPopMatrix();
			glPopMatrix();
			//end right arm
		

		//tail
		glPushMatrix();
		setDiffuseColor(0.58, 0.31, 0.04);
		if (VAL(METABALLS)) {
			
			glTranslated(0, 0, -0.125);
			glScaled(1 / 1.5, 1 / 0.75, 1.0 / 2);
			double scl = 1.2;
			glScaled(0.17 * scl, 0.15 * scl, 0.22 * scl);
			mb->set_ball(0, 0, 0, 0);
			int seg_dis = 7;
			double curr_theta = VAL(TAIL), curr_y = seg_dis * sin(curr_theta / 180.0 * M_PI), curr_z = -seg_dis * cos(curr_theta / 180.0 * M_PI);
			mb->set_ball(1, 0, curr_y, curr_z);
			curr_theta += VAL(TAIL);
			curr_y += seg_dis * sin(curr_theta / 180.0 * M_PI);
			curr_z += -seg_dis * cos(curr_theta / 180.0 * M_PI);
			mb->set_ball(2, 0, curr_y, curr_z);
			curr_theta += VAL(TAIL);
			curr_y += seg_dis * sin(curr_theta / 180.0 * M_PI);
			curr_z += -seg_dis * cos(curr_theta / 180.0 * M_PI);
			mb->set_ball(3, 0, curr_y, curr_z);
			curr_theta += VAL(TAIL);
			curr_y += seg_dis * sin(curr_theta / 180.0 * M_PI);
			curr_z += -seg_dis * cos(curr_theta / 180.0 * M_PI);
			mb->set_ball(4, 0, curr_y, curr_z);
			/*mb->set_ball(3, 0, 0, -18);
			mb->set_ball(4, 0, 0, -24);*/
			mc->calMetaBalls();
			mc->drawMarchingCube();
			//sting
			glPushMatrix();
			//setDiffuseColor(0, 1, 1);

			glTranslated(0, curr_y, curr_z);
			glRotated(-180 + curr_theta, 1, 0, 0);
			drawCylinder(5, 1, .25);
			glPopMatrix();
		}
		else {
			glScaled(1, 1.5, 1);
			glRotated(VAL(TAIL), 1, 0, 0);
			glTranslated(0, 0, -0.6);
			drawCylinder(0.75, .23, .23);
			glRotated(VAL(TAIL), 1, 0, 0);
			glTranslated(0, 0, -0.6);
			drawCylinder(0.75, .21, .21);
			glRotated(VAL(TAIL), 1, 0, 0);
			glTranslated(0, 0, -0.6);
			drawCylinder(0.75, .19, .19);
			glRotated(VAL(TAIL), 1, 0, 0);
			glTranslated(0, 0, -0.6);
			drawCylinder(0.75, .17, .17);
			glRotated(VAL(TAIL), 1, 0, 0);
			glTranslated(0, 0, -0.6);
			drawCylinder(0.75, .15, .15);
			//sting
			glPushMatrix();
			//setDiffuseColor(0, 1, 1);
			glTranslated(0, 0, -0.05);
			drawCylinder(0.1, .05, .05);
			drawTriangle(0, 0, -0.2, -0.2, 0, 0, 0.2, 0, 0);
			glPopMatrix();
		}
		glPopMatrix();
		//end tail


				right_leg(leg_back);
				right_leg(leg_mid);
				right_leg(leg_front);

				left_leg(leg_back);
				left_leg(leg_mid);
				left_leg(leg_front);
		

	glPopMatrix();
	endDraw();
}

void ScorpionModel::left_leg(double pos) {
	glPushMatrix();
	setDiffuseColor(0.56,0.39,0.12);
	glScaled(1 / 1.5, 1 / 0.75, 0.5);
	glRotated(-90, 0.0, 1.0, 0.0);
	glTranslated(-pos, 0, 0.75);
	glRotated(-25, 1.0, 0.0, 0.0);
	drawCylinder(0.6, .15, .15);
	glRotated(VAL(L_LEG), 0.0, 0.0, 1.0);
	glRotated(45, 1.0, 0.0, 0.0);
	
	glTranslated(0, cos45 / 2, 0.25);
	drawCylinder(0.5, .15, .15);
	glRotated(40, 0.0, 1.0, 0.0);
	glRotated(10, 1.0, 0.0, 0.0);
	glTranslated(-.3, 0, 0.3);
	drawCylinder(1, .15, .05);
	glPopMatrix();
}

void ScorpionModel::right_leg(double pos) {
	glPushMatrix();
	setDiffuseColor(0.56, 0.39, 0.12);
	glScaled(1 / 1.5, 1 / 0.75, 0.5);
	glRotated(90, 0.0, 1.0, 0.0);
	glTranslated(pos, 0, 0.75);
	glRotated(-25, 1.0, 0.0, 0.0);
	drawCylinder(0.6, .15, .15);
	glRotated(VAL(R_LEG), 0.0, 0.0, 1.0);
	glRotated(45, 1.0, 0.0, 0.0);
	glTranslated(0, cos45 / 2, 0.25);
	drawCylinder(0.5, .15, .15);
	glRotated(-40, 0.0, 1.0, 0.0);
	glRotated(10, 1.0, 0.0, 0.0);
	glTranslated(.3, 0, 0.3);
	drawCylinder(1, .15, .05);
	glPopMatrix();
}

void ScorpionModel::houdini_lsystem() {
	int level = VAL(L_SIZE);
	gen_st_pattern(level);
	draw_lsystem(level);
}
void ScorpionModel::gen_st_pattern(int level) {
	st_pattern = l_init;
	for (int i = 0; i < level; ++i) {
		std::string temp;
		for (int j = 0; j < st_pattern.length(); ++j) {
			if (st_pattern[j] == 'F') {
				temp += F_transform;
			}
			else if (st_pattern[j] == 'G') {
				temp += G_transform;
			}
			else {
				temp += st_pattern[j];
			}
		}
		st_pattern = temp;
	}
}
void ScorpionModel::draw_lsystem(double level) {
	double start_pos[] = {0, 0.5, 0};
	double curr_pos[]= { 0, 0.5, 0};
	int curr_angle=0;
	//glBegin(GL_LINE_STRIP);
	int curr_color = 0;

	setAmbientColor(.5f, .5f, .5f);
	setDiffuseColor(1,0.718,0.773);
	glBegin(GL_LINE_STRIP);
	int point_cout = 1;
	//glColor3ubv(color[curr_color++]);
	glVertex3d(start_pos[0], start_pos[1], start_pos[2]);
	for (int i = 0; i < st_pattern.length(); ++i) {
		switch (st_pattern[i])
		{
		case 'F':
		case 'G':
			curr_pos[0] += l_length / (pow(3,level)) * cos(curr_angle / 180.0 * M_PI);
			//curr_pos[1] *= -1;
			curr_pos[2] += l_length / (pow(3,level)) * sin(curr_angle / 180.0 * M_PI);
			
			glVertex3d(curr_pos[0], curr_pos[1], curr_pos[2]);
			break;
		case '+':
			curr_angle += l_angle;
			curr_angle %= 360;
			break;
		case '-':
			curr_angle -= l_angle;
			curr_angle %= 360;
			break;
		default:
			break;
		}
	}
	glEnd();
}

int main()
{
	// Initialize the controls
	// Constructor is ModelerControl(name, minimumvalue, maximumvalue, 
	// stepsize, defaultvalue)
	ModelerControl controls[NUMCONTROLS];
	controls[XPOS] = ModelerControl("X Position", -5, 5, 0.1f, 0);
	controls[YPOS] = ModelerControl("Y Position", 0, 5, 0.1f, 0);
	controls[ZPOS] = ModelerControl("Z Position", -5, 5, 0.1f, 0);
	controls[L_CLAW] = ModelerControl("Left Claw", -85, -50, 1,-75);
	controls[LF_CLAW] = ModelerControl("Left Front Claw", 5, 25, 1, 15);
	controls[R_CLAW] = ModelerControl("Right Claw", 50, 85, 1, 75);
	controls[RF_CLAW] = ModelerControl("Right Front Claw", 5, 25, 1, 15);
	controls[TAIL] = ModelerControl("Tail", 0, 45, 1, 40);
	controls[L_LEG] = ModelerControl("Left Legs", -45, 45, 1, 0);
	controls[R_LEG] = ModelerControl("Right Legs", -45, 45, 1, 0);
	controls[ENABLE_L] = ModelerControl("Enable L-System", 0, 1, 1, 0);
	controls[L_SIZE] = ModelerControl("L-System level", 0,6, 1, 2);
	controls[LIGHT_X] = ModelerControl("Light Position X", -30, 30, 1, -2);
	controls[LIGHT_Y] = ModelerControl("Light Position Y", -30, 30, 1, 1);
	controls[LIGHT_Z] = ModelerControl("Light Position Z", -30, 30, 1, 5);
	controls[LIGHT_INTENSITY] = ModelerControl("Light Intensity", 0, 5, 0.1, 1.3);
	controls[FOG_DENSITY] = ModelerControl("Fog Density", 0, 4, 1, 0);
	controls[METABALLS] = ModelerControl("Change to Metaballs", 0, 1, 1, 0);
	//controls[MTBALL_STEP] = ModelerControl("Metaballs Step", 0.6, 1, 0.1f, 0.8f);

	ModelerApplication::Instance()->Init(&createScorpionModel, controls, NUMCONTROLS);
	return ModelerApplication::Instance()->Run();
}