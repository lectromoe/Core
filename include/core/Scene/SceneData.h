/*
 MIT License
 
 Copyright (c) 2021 lectroMathew <contact@lectro.moe>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */
#ifndef CORE_SCENEDATA_H
#define CORE_SCENEDATA_H

#include "core/Essentials.h"

#include <Corrade/Containers/Array.h>
#include <Corrade/Containers/Optional.h>
#include <Magnum/GL/Mesh.h>
#include <Magnum/GL/Renderer.h>
#include <Magnum/GL/Texture.h>
#include <Magnum/GL/TextureFormat.h>
#include <Magnum/Trade/PhongMaterialData.h>
#include <Magnum/Trade/SceneData.h>

#include <core/Logger.h>

using namespace Magnum;
namespace core {

struct SceneData {
    Containers::Optional<Trade::SceneData> childrenData;
    Containers::Array<Containers::Optional<GL::Mesh>> meshes;
    Containers::Array<Containers::Optional<GL::Texture2D>> textures;
    Containers::Array<Containers::Optional<Trade::MaterialData>> materials;
};

}

#endif //CORE_SCENEDATA_H
