#ifndef LEARNED_MODEL__SIMPLE_PYMODEL_HPP_
#define LEARNED_MODEL__SIMPLE_PYMODEL_HPP_

#include "learned_model/model_connections_helpers.hpp"
#include "learned_model/submodel_interface.hpp"

#include <pybind11/embed.h>
#include <pybind11/stl.h>

namespace py = pybind11;

/**
 * @class SimModelPymodels
 * @brief This class is an interface between C++ and python models.
 */
class SimplePymodel : public SubModelInterface
{
private:
  std::string pymodel_import_name;

  int num_inputs_py;
  int num_outputs_py;

  py::object py_model_class;

  std::vector<int>
    map_sig_vec_to_pyin;  // index in "map_sig_vec_to_pyin" is index in "py_inputs" and value in
                          // "map_sig_vec_to_pyin" is index in "signals_vec_names"
  std::vector<int>
    map_pyout_to_sig_vec;  // index in "map_pyout_to_sig_vec" is index in "pymodel_outputs" and
                           // value in "map_pyout_to_sig_vec" is index in "signals_vec_names"

  std::vector<char *> pymodel_input_names;
  std::vector<char *> pymodel_state_names;

public:
  /**
   * @brief constructor
   * @param [in] pymodel_import_name_ path to python model
   * @param [in] param_file_path path to saved parameter file of the python sub-model
   * @param [in] py_class_name name of the python class
   */
  SimplePymodel(std::string pymodel_import_name_, std::string param_file_path, std::string py_class_name);

  /**
   * @brief calculate the next state of a python model
   * @param [in] model_signals_vec all available inputs from PSIM
   */
  std::vector<double> getNextState(
    std::vector<double> model_signals_vec, std::vector<double> model_signals_vec_next) override;

  /**
   * @brief set time step of the model
   * @param [in] dt time step
   */
  void dtSet(double dt) override;

  /**
   * @brief get names of inputs of python model
   */
  std::vector<char *> getInputNames() override;

  /**
   * @brief get names of states of python model
   */
  std::vector<char *> getStateNames() override;

  /**
   * @brief create a map from model signal vector to python model inputs
   * @param [in] signal_vec_names names of signals in model signal vector
   */
  void mapInputs(std::vector<char *> signals_vec_names) override;

  /**
   * @brief create a map from python outputs to model signal vector
   * @param [in] signal_vec_names names of signals in model signal vector
   */
  void mapOutputs(std::vector<char *> signals_vec_names) override;

};

#endif  // LEARNED_MODEL__SIMPLE_PYMODEL_HPP_