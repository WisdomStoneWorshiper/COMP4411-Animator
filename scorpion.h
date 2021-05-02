#pragma once

#include "modelerview.h"
#include "modelerapp.h"
#include "modelerdraw.h"
#include <FL/gl.h>

#include <string>
#include "marchingcube.h"
#include "metaballs.h"
#include "bitmap.h"



class ScorpionModel : public ModelerView
{
public:
    ScorpionModel(int x, int y, int w, int h, char* label);

    virtual void draw();

private:
    void houdini_lsystem();
    void gen_st_pattern(int level);
    void draw_lsystem(double level);
    std::string st_pattern;


    void right_leg(double pos);
    void left_leg(double pos);
    MarchingCube* mc;
    Metaballs* mb;
   
    
};

ModelerView* createScorpionModel(int x, int y, int w, int h, char* label);