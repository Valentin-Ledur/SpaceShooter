#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "Game/AIData.hpp"
#include "Game/Game.hpp"

namespace py = pybind11;

PYBIND11_MODULE(SpaceShooter_IA, m)
{
    m.doc() = "Environnement SpaceShooter 2D C++ pour TensorFlow";

    py::class_<AIDataOutput>(m, "AIDataOutput")
        .def(py::init<>())
        .def_readwrite("up", &AIDataOutput::up)
        .def_readwrite("down", &AIDataOutput::down)
        .def_readwrite("left", &AIDataOutput::left)
        .def_readwrite("right", &AIDataOutput::right)
        .def_readwrite("shoot", &AIDataOutput::shoot)
        .def_readwrite("x", &AIDataOutput::x)
        .def_readwrite("y", &AIDataOutput::y);

    py::class_<Game>(m, "Game")
        .def(py::init<>())
        .def("reset", &Game::Reset)
        .def("step", &Game::Step, py::arg("ai_output"));
}