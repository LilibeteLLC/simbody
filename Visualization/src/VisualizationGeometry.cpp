/* -------------------------------------------------------------------------- *
 *                      SimTK Core: SimTK Simbody(tm)                         *
 * -------------------------------------------------------------------------- *
 * This is part of the SimTK Core biosimulation toolkit originating from      *
 * Simbios, the NIH National Center for Physics-Based Simulation of           *
 * Biological Structures at Stanford, funded under the NIH Roadmap for        *
 * Medical Research, grant U54 GM072970. See https://simtk.org.               *
 *                                                                            *
 * Portions copyright (c) 2010 Stanford University and the Authors.           *
 * Authors: Peter Eastman                                                     *
 * Contributors:                                                              *
 *                                                                            *
 * Permission is hereby granted, free of charge, to any person obtaining a    *
 * copy of this software and associated documentation files (the "Software"), *
 * to deal in the Software without restriction, including without limitation  *
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,   *
 * and/or sell copies of the Software, and to permit persons to whom the      *
 * Software is furnished to do so, subject to the following conditions:       *
 *                                                                            *
 * The above copyright notice and this permission notice shall be included in *
 * all copies or substantial portions of the Software.                        *
 *                                                                            *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,   *
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL    *
 * THE AUTHORS, CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,    *
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR      *
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE  *
 * USE OR OTHER DEALINGS IN THE SOFTWARE.                                     *
 * -------------------------------------------------------------------------- */

#include "simbody/internal/VisualizationGeometry.h"
#include "simbody/internal/SimbodyMatterSubsystem.h"

using namespace SimTK;

static const Vec3 DefaultBodyColor = Gray;

VisualizationGeometry::VisualizationGeometry(const Visualizer& visualizer, const SimbodyMatterSubsystem& matter, const State& state) :
        visualizer(visualizer), matter(matter), state(state) {
}

void VisualizationGeometry::implementLineGeometry(const SimTK::DecorativeLine& geom) {

}

void VisualizationGeometry::implementBrickGeometry(const SimTK::DecorativeBrick& geom) {
    const Transform& transform  = matter.getMobilizedBody(MobilizedBodyIndex(geom.getBodyId())).getBodyTransform(state);
    visualizer.drawBox(transform*geom.getTransform(), geom.getHalfLengths(), getColor(geom), getRepresentation(geom));
}

void VisualizationGeometry::implementCylinderGeometry(const SimTK::DecorativeCylinder& geom) {

}

void VisualizationGeometry::implementCircleGeometry(const SimTK::DecorativeCircle& geom) {

}

void VisualizationGeometry::implementSphereGeometry(const SimTK::DecorativeSphere& geom) {
    const Transform& transform  = matter.getMobilizedBody(MobilizedBodyIndex(geom.getBodyId())).getBodyTransform(state);
    visualizer.drawEllipsoid(transform*geom.getTransform(), Vec3(geom.getRadius()), getColor(geom), getRepresentation(geom));
}

void VisualizationGeometry::implementEllipsoidGeometry(const SimTK::DecorativeEllipsoid& geom) {
    const Transform& transform  = matter.getMobilizedBody(MobilizedBodyIndex(geom.getBodyId())).getBodyTransform(state);
    visualizer.drawEllipsoid(transform*geom.getTransform(), geom.getRadii(), getColor(geom), getRepresentation(geom));
}

void VisualizationGeometry::implementFrameGeometry(const SimTK::DecorativeFrame& geom) {

}

void VisualizationGeometry::implementTextGeometry(const SimTK::DecorativeText& geom) {

}

void VisualizationGeometry::implementMeshGeometry(const SimTK::DecorativeMesh& geom) {

}

Vec4 VisualizationGeometry::getColor(const DecorativeGeometry& geom) const {
    Vec4 result;
    result.updSubVec<3>(0) = (geom.getColor()[0] == -1 ? DefaultBodyColor : geom.getColor());
    result[3] = (geom.getOpacity() < 0 ? 1 : geom.getOpacity());
    return result;
}

int VisualizationGeometry::getRepresentation(const DecorativeGeometry& geom) const {
    if (geom.getRepresentation() == DecorativeGeometry::DrawDefault)
        return DecorativeGeometry::DrawSurface;
    return geom.getRepresentation();
}
