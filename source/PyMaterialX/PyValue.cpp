//
// TM & (c) 2017 Lucasfilm Entertainment Company Ltd. and Lucasfilm Ltd.
// All rights reserved.  See LICENSE.txt for license.
//

#include <PyMaterialX/PyMaterialX.h>

#include <MaterialXCore/Value.h>

#include <PyBind11/stl.h>

#define BIND_TYPE_INSTANCE(NAME, T, PYTYPE)                                                                                 \
py::class_<mx::TypedValue<T>, std::shared_ptr< mx::TypedValue<T> >, mx::Value>(mod, "TypedValue_" #NAME, py::metaclass())   \
    .def("getData", [](const mx::TypedValue<T>& value) { return PYTYPE(value.getData()); })                                 \
    .def("getValueString", [](const mx::TypedValue<T>& value) { return PyDefaultString(value.getValueString()); })          \
    .def_static("createValue", &mx::Value::createValue<T>)                                                                  \
    .def_readonly_static("TYPE", &mx::TypedValue<T>::TYPE)                                                                  \
    .def_readonly_static("ZERO", &mx::TypedValue<T>::ZERO);

namespace py = pybind11;
namespace mx = MaterialX;

void bindPyValue(py::module& mod)
{
    py::class_<mx::Value, mx::ValuePtr>(mod, "Value")
        .def("getValueString", &mx::Value::getValueString)
        .def("getTypeString", &mx::Value::getTypeString)
        .def_static("createValueFromStrings", &mx::Value::createValueFromStrings);

    BIND_TYPE_INSTANCE(integer, int, py::int_)
    BIND_TYPE_INSTANCE(boolean, bool, bool)
    BIND_TYPE_INSTANCE(float, float, float)
    BIND_TYPE_INSTANCE(color2, mx::Color2, mx::Color2)
    BIND_TYPE_INSTANCE(color3, mx::Color3, mx::Color3)
    BIND_TYPE_INSTANCE(color4, mx::Color4, mx::Color4)
    BIND_TYPE_INSTANCE(vector2, mx::Vector2, mx::Vector2)
    BIND_TYPE_INSTANCE(vector3, mx::Vector3, mx::Vector3)
    BIND_TYPE_INSTANCE(vector4, mx::Vector4, mx::Vector4)
    BIND_TYPE_INSTANCE(matrix33, mx::Matrix3x3, mx::Matrix3x3)
    BIND_TYPE_INSTANCE(matrix44, mx::Matrix4x4, mx::Matrix4x4)
    BIND_TYPE_INSTANCE(string, std::string, PyDefaultString)
}
