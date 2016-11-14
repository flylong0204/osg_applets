/* OpenSceneGraph example, osgparticle.
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy
*  of this software and associated documentation files (the "Software"), to deal
*  in the Software without restriction, including without limitation the rights
*  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*  copies of the Software, and to permit persons to whom the Software is
*  furnished to do so, subject to the following conditions:
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
*  THE SOFTWARE.
*/

#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Group>
#include <osg/Geode>

#include <osgParticle/Particle>
#include <osgParticle/ParticleSystem>
#include <osgParticle/ParticleSystemUpdater>
#include <osgParticle/ModularEmitter>
#include <osgParticle/ModularProgram>
#include <osgParticle/RandomRateCounter>
#include <osgParticle/SectorPlacer>
#include <osgParticle/RadialShooter>
#include <osgParticle/AccelOperator>
#include <osgParticle/FluidFrictionOperator>

osgParticle::ParticleSystem *create_simple_particle_system(osg::Group *root)
{

    osgParticle::ParticleSystem *ps = new osgParticle::ParticleSystem;

    ps->setDefaultAttributes("", true, false);

    osgParticle::ModularEmitter *emitter = new osgParticle::ModularEmitter;

    emitter->setParticleSystem(ps);

    osgParticle::RandomRateCounter *rrc = 
        static_cast<osgParticle::RandomRateCounter *>(emitter->getCounter());

    rrc->setRateRange(20, 30);    // generate 20 to 30 particles per second

    root->addChild(emitter);

    osg::Geode *geode = new osg::Geode;    
    geode->addDrawable(ps);

    // add the geode to the scene graph
    root->addChild(geode);

    return ps;

}

void build_world(osg::Group *root)
{
    osgParticle::ParticleSystem *ps1 = create_simple_particle_system(root);

    osgParticle::ParticleSystemUpdater *psu = new osgParticle::ParticleSystemUpdater;
    psu->addParticleSystem(ps1);

    // add the updater node to the scene graph
    root->addChild(psu);
}

int main(int, char **)
{
    // construct the viewer.
    osgViewer::Viewer viewer;
    
    osg::Group *root = new osg::Group;
    build_world(root);
   
    // add the stats handler
    viewer.addEventHandler(new osgViewer::StatsHandler);

    // add a viewport to the viewer and attach the scene graph.
    viewer.setSceneData(root);
        
    return viewer.run();
}
