# Install script for directory: D:/Git/OpenglLearn/assimp-5.2.5/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.2.4-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Git/OpenglLearn/assimp-5.2.5/build/lib/Debug/assimp-vc143-mtd.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Git/OpenglLearn/assimp-5.2.5/build/lib/Release/assimp-vc143-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Git/OpenglLearn/assimp-5.2.5/build/lib/MinSizeRel/assimp-vc143-mt.lib")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/Git/OpenglLearn/assimp-5.2.5/build/lib/RelWithDebInfo/assimp-vc143-mt.lib")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "libassimp5.2.4" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Git/OpenglLearn/assimp-5.2.5/build/bin/Debug/assimp-vc143-mtd.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Git/OpenglLearn/assimp-5.2.5/build/bin/Release/assimp-vc143-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Git/OpenglLearn/assimp-5.2.5/build/bin/MinSizeRel/assimp-vc143-mt.dll")
  elseif(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/Git/OpenglLearn/assimp-5.2.5/build/bin/RelWithDebInfo/assimp-vc143-mt.dll")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/anim.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/aabb.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/ai_assert.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/camera.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/color4.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/color4.inl"
    "D:/Git/OpenglLearn/assimp-5.2.5/build/code/../include/assimp/config.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/ColladaMetaData.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/commonMetaData.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/defs.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/cfileio.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/light.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/material.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/material.inl"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/matrix3x3.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/matrix3x3.inl"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/matrix4x4.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/matrix4x4.inl"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/mesh.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/ObjMaterial.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/pbrmaterial.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/GltfMaterial.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/postprocess.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/quaternion.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/quaternion.inl"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/scene.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/metadata.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/texture.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/types.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/vector2.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/vector2.inl"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/vector3.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/vector3.inl"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/version.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/cimport.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/importerdesc.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Importer.hpp"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/DefaultLogger.hpp"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/ProgressHandler.hpp"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/IOStream.hpp"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/IOSystem.hpp"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Logger.hpp"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/LogStream.hpp"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/NullLogger.hpp"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/cexport.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Exporter.hpp"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/DefaultIOStream.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/DefaultIOSystem.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/ZipArchiveIOSystem.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/SceneCombiner.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/fast_atof.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/qnan.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/BaseImporter.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Hash.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/MemoryIOWrapper.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/ParsingUtils.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/StreamReader.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/StreamWriter.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/StringComparison.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/StringUtils.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/SGSpatialSort.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/GenericProperty.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/SpatialSort.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/SkeletonMeshBuilder.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/SmallVector.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/SmoothingGroups.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/SmoothingGroups.inl"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/StandardShapes.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/RemoveComments.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Subdivision.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Vertex.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/LineSplitter.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/TinyFormatter.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Profiler.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/LogAux.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Bitmap.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/XMLTools.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/IOStreamBuffer.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/CreateAnimMesh.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/XmlParser.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/BlobIOSystem.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/MathFunctions.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Exceptional.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/ByteSwapper.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Base64.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "assimp-dev" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Compiler/pushpack1.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Compiler/poppack1.h"
    "D:/Git/OpenglLearn/assimp-5.2.5/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Git/OpenglLearn/assimp-5.2.5/build/code/Debug/assimp-vc143-mtd.pdb")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "D:/Git/OpenglLearn/assimp-5.2.5/build/code/RelWithDebInfo/assimp-vc143-mt.pdb")
  endif()
endif()

