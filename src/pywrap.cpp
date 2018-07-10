#include <servoce/servoce.h>
#include <servoce/display.h>
//#include <gxx/util/base64.h>

#include <pybind11/pybind11.h>
#include <pybind11/operators.h>
#include <pybind11/stl.h>
namespace py = pybind11;

#define DEF_TRANSFORM_OPERATIONS(TYPE) 				\
.def("transform", &TYPE::transform)				\
.def("translate", &TYPE::translate)							\
.def("up", &TYPE::up)							\
.def("down", &TYPE::down)						\
.def("right", &TYPE::right)						\
.def("left", &TYPE::left)						\
.def("forw", &TYPE::forw)						\
.def("back", &TYPE::back)						\
.def("rotateX", &TYPE::rotateX)					\
.def("rotateY", &TYPE::rotateY)					\
.def("rotateZ", &TYPE::rotateZ)					\
.def("mirrorX", &TYPE::mirrorX)					\
.def("mirrorY", &TYPE::mirrorY)					\
.def("mirrorZ", &TYPE::mirrorZ)					\
.def("mirrorXY", &TYPE::mirrorXY)				\
.def("mirrorYZ", &TYPE::mirrorYZ)				\
.def("mirrorXZ", &TYPE::mirrorXZ)			

PYBIND11_MODULE(libservoce, m) {
	//py::register_exception<servoce::RuntimeException>(m, "ServoceRuntimeException");

/*	py::class_<servoce::point3>(m, "point3")
		//DEF_TRANSFORM_OPERATIONS(servoce::point3)
		.def(py::init<double,double,double>())
		.def(py::init<double,double>())
		.def_readwrite("x", &servoce::point3::x)
		.def_readwrite("y", &servoce::point3::y)
		.def_readwrite("z", &servoce::point3::z)
	;
	
	py::class_<servoce::vector3>(m, "vector3")
		//DEF_TRANSFORM_OPERATIONS(servoce::vector3)
		.def(py::init<double,double,double>())
		.def(py::init<double,double>())
		.def_readwrite("x", &servoce::vector3::x)
		.def_readwrite("y", &servoce::vector3::y)
		.def_readwrite("z", &servoce::vector3::z)
	;*/

	py::class_<servoce::shape>(m, "Shape")/*
		.def("__add__", &servoce::shape::operator+)
		.def("__sub__", &servoce::shape::operator-)
		.def("__xor__", &servoce::shape::operator^)
	*/
		//.def(py::pickle(
        	//[](const servoce::shape &self) { return gxx::base64_encode(self.string_dump()); },
        	//[](const std::string& in) { return servoce::shape::restore_string_dump(gxx::base64_decode(in)); }
    	//))
    ;

	/*py::class_<servoce::shape, servoce::shape>(m, "Solid")
		DEF_TRANSFORM_OPERATIONS(servoce::shape)
		.def("__add__", &servoce::shape::operator+)
		.def("__sub__", &servoce::shape::operator-)
		.def("__xor__", &servoce::shape::operator^)
		//.def(py::self - servoce::shape)
		//.def(py::self ^ servoce::shape)
		.def("fillet", &servoce::shape::fillet, py::arg("r"), py::arg("nums"))

		.def(py::pickle(
        	[](const servoce::shape &self) { return gxx::base64_encode(self.string_dump()); },
        	[](const std::string& in) { return servoce::shape::restore_string_dump(gxx::base64_decode(in)).to_shape(); }
    	))
    ;*/
	
/**/
	m.def("make_box", 		servoce::make_box, py::arg("x"), py::arg("y"), py::arg("z"), py::arg("center") = false);
	m.def("make_sphere", 	servoce::make_sphere, py::arg("r"));
	m.def("make_cylinder", 	servoce::make_cylinder, py::arg("r"), py::arg("h"), py::arg("center") = false);
	m.def("make_cone", 		servoce::make_cone, py::arg("r1"), py::arg("r2"), py::arg("h"), py::arg("center") = false);
	m.def("make_torus", 	servoce::make_torus, py::arg("r1"), py::arg("r2"));

	m.def("make_linear_extrude", (servoce::shape(*)(const servoce::shape&,const servoce::vector3&,bool)) &servoce::make_linear_extrude, py::arg("shp"), py::arg("vec"), py::arg("center")=false);
	m.def("make_linear_extrude", (servoce::shape(*)(const servoce::shape&,double,bool)) &servoce::make_linear_extrude, py::arg("shp"), py::arg("z"), py::arg("center")=false);
	m.def("make_pipe", 			servoce::make_pipe, py::arg("prof"), py::arg("path"));
	m.def("make_pipe_shell", 	servoce::make_pipe_shell, py::arg("prof"), py::arg("path"), py::arg("isFrenet") = false);
/*
	py::class_<servoce::shape, servoce::shape>(m, "Face")
		DEF_TRANSFORM_OPERATIONS(servoce::shape)
		.def("__add__", &servoce::shape::operator+)
		.def("__sub__", &servoce::shape::operator-)
		.def("__xor__", &servoce::shape::operator^)
		.def("fillet", &servoce::shape::fillet, py::arg("r"), py::arg("nums"))
		.def("wires", &servoce::shape::wires)
	;*/
	m.def("make_circle", 	servoce::make_circle, py::arg("r"));
	m.def("make_ngon", 		servoce::make_ngon, py::arg("r"), py::arg("n"));
	m.def("make_square", 	servoce::make_square, py::arg("a"), py::arg("center") = false);
	m.def("make_rectangle", servoce::make_rectangle, py::arg("a"), py::arg("b"), py::arg("center") = false);
	m.def("make_polygon", 	(servoce::shape(*)(const std::vector<servoce::point3>&))&servoce::make_polygon, py::arg("pnts"));
	//m.def("make_sweep", 	servoce::make_sweep, py::arg("prof"), py::arg("path"));
/*
	py::class_<servoce::wire, servoce::shape>(m, "Wire")
		DEF_TRANSFORM_OPERATIONS(servoce::wire)
		.def("__add__", &servoce::wire::operator+)
		.def("__sub__", &servoce::wire::operator-)
		.def("__xor__", &servoce::wire::operator^)
		.def("shape", &servoce::wire::to_shape)
	;
	
	m.def("make_segment", servoce::curve::make_segment);
	m.def("make_polysegment", servoce::curve::make_polysegment, py::arg("pnts"), py::arg("closed") = false);
	m.def("make_interpolate", (servoce::wire(*)(const std::vector<servoce::point3>&, const std::vector<servoce::vector3>&, bool))&servoce::curve::make_interpolate, py::arg("pnts"), py::arg("tang"), py::arg("closed") = false);
	m.def("make_interpolate", (servoce::wire(*)(const std::vector<servoce::point3>&, const bool))&servoce::curve::make_interpolate, py::arg("pnts"), py::arg("closed") = false);
	m.def("make_helix", servoce::curve::make_helix, py::arg("step"), py::arg("height"), py::arg("radius"), py::arg("angle") = 0, py::arg("leftHanded") = false, py::arg("newStyle") = true);
	m.def("make_long_helix", servoce::curve::make_long_helix, py::arg("step"), py::arg("height"), py::arg("radius"), py::arg("angle") = 0, py::arg("leftHanded") = false);
	m.def("make_complex_wire", servoce::curve::make_complex_wire, py::arg("wires"));
	m.def("make_wcircle", (servoce::wire(*)(double))&servoce::curve::make_circle);
	m.def("make_wcircle", (servoce::wire(*)(double,double,double))&servoce::curve::make_circle);

	py::class_<servoce::sweep_shape, servoce::shape>(m, "SolidSweep");
	py::class_<servoce::sweep_shape, servoce::shape>(m, "FaceSweep");
	*/
	py::class_<servoce::color>(m, "Color")
		.def(py::init<float, float, float>());
	py::class_<servoce::scene>(m, "Scene")
		.def(py::init<>())
		.def("add", (void(servoce::scene::*)(const servoce::shape&, servoce::color))&servoce::scene::add, py::arg("shape"), py::arg("color") = servoce::color())
		.def("add", (void(servoce::scene::*)(const servoce::point3&, servoce::color))&servoce::scene::add, py::arg("shape"), py::arg("color") = servoce::color())
		.def("append", (void(servoce::scene::*)(const servoce::scene&))&servoce::scene::append, py::arg("scene"))
	;
/*
	m.def("make_union", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::boolops::make_union);
	m.def("make_difference", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::boolops::make_difference);
	m.def("make_intersect", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::boolops::make_intersect);

	m.def("make_union", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::boolops::make_union);
	m.def("make_difference", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::boolops::make_difference);
	m.def("make_intersect", (servoce::shape(*)(const std::vector<const servoce::shape*>&))&servoce::boolops::make_intersect);
*/
	m.def("display_scene", 	servoce::display);
/*
	py::class_<servoce::trans::transformation>(m, "transformation")
		//.def(py::init<>())
		.def("__call__", (servoce::shape(servoce::trans::transformation::*)(const servoce::shape&)const)&servoce::trans::transformation::operator())
		.def("__call__", (servoce::shape(servoce::trans::transformation::*)(const servoce::shape&)const)&servoce::trans::transformation::operator())
		.def("__call__", (servoce::wire(servoce::trans::transformation::*)(const servoce::wire&)const)&servoce::trans::transformation::operator())
		.def("__call__", (servoce::trans::transformation(servoce::trans::transformation::*)(const servoce::trans::transformation&)const)&servoce::trans::transformation::operator())
		.def("__mul__", &servoce::trans::transformation::operator* )

		.def(py::pickle(
        	[](const servoce::trans::transformation &self) { return gxx::base64_encode(self.string_dump()); },
        	[](const std::string& in) { return servoce::trans::transformation::restore_string_dump(gxx::base64_decode(in)); }
    	))
	;

	//py::class_<servoce::trans::translate, servoce::trans::transformation>(m, "translate")
	//	.def(py::init<double,double,double>());
	//py::class_<servoce::trans::axrotation, servoce::trans::transformation>(m, "axrotation")
	//	.def(py::init<double,double,double,double>());
	//py::class_<servoce::trans::axis_mirror, servoce::trans::transformation>(m, "axis_mirror")
	//	.def(py::init<double,double,double>());
	//py::class_<servoce::trans::plane_mirror, servoce::trans::transformation>(m, "plane_mirror")
	//	.def(py::init<double,double,double>());
	m.def("translate", (servoce::trans::transformation(*)(double,double,double)) &servoce::trans::translate);
	m.def("translate", (servoce::trans::transformation(*)(double,double)) &servoce::trans::translate);
	m.def("translate", (servoce::trans::transformation(*)(const servoce::vector3&)) &servoce::trans::translate);
	m.def("axrotation", servoce::trans::axrotation);
	m.def("axis_mirror", servoce::trans::axis_mirror);
	m.def("plane_mirror", servoce::trans::plane_mirror);

	m.def("rotateX", servoce::trans::rotateX);
	m.def("rotateY", servoce::trans::rotateY);
	m.def("rotateZ", servoce::trans::rotateZ);
	m.def("mirrorX", servoce::trans::mirrorX);
	m.def("mirrorY", servoce::trans::mirrorY);
	m.def("mirrorZ", servoce::trans::mirrorZ);
	m.def("mirrorXY", servoce::trans::mirrorXY);
	m.def("mirrorXZ", servoce::trans::mirrorXZ);
	m.def("mirrorYZ", servoce::trans::mirrorYZ);
	m.def("up", servoce::trans::up);
	m.def("down", servoce::trans::down);
	m.def("left", servoce::trans::left);
	m.def("right", servoce::trans::right);
	m.def("forw", servoce::trans::forw);
	m.def("back", servoce::trans::back);









	m.def("simplify_with_bspline", &servoce::curve::simplify_with_bspline);
	m.def("make_stl", &servoce::make_stl);
*/

}