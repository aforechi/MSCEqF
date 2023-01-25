// Copyright (C) 2023 Alessandro Fornasier.
// Control of Networked Systems, University of Klagenfurt, Austria.
//
// All rights reserved.
//
// This software is licensed under the terms of the BSD-2-Clause-License with
// no commercial use allowed, the full terms of which are made available
// in the LICENSE file. No license in patents is granted.
//
// You can contact the authors at <alessandro.fornasier@ieee.org>

#ifndef MSCEQF_OPTIONS_HPP
#define MSCEQF_OPTIONS_HPP

#include "types/fptypes.hpp"

namespace msceqf
{

enum class FeatureRepresentation
{
  EUCLIDEAN,
  ANCHORED_POLAR,
  ANCHORED_INVERSE_DEPTH
};

struct StateOptions
{
  /// initial covariance values
  Matrix9 D_init_cov_;      //!< Initial covariance of the D element of the state
  Matrix6 delta_init_cov_;  //!< Initial covariance of the delta element of the state
  Matrix6 E_init_cov_;      //!< Initial covariance of the E element of the state
  Matrix4 L_init_cov_;      //!< Initial covariance of the L element of the state

  /// Initial calibration values (or calibration values to be used if no online calibration is activated)
  SE3 initial_camera_extrinsics_;
  In initial_camera_intrinsics_;

  /// Filter flags
  bool enable_camera_extrinsics_calibration_;  //!< Boolean to enable estrinsic camera calibration
  bool enable_camera_intrinsics_calibration_;  //!< Boolean to enable intinsic camera calibration

  /// State and filter options
  fp gravity_;                    //!< The magnitude of the gravity vector in m/s^2
  uint num_clones_;               //!< The maximum number of stochastic clones
  uint num_persistent_features_;  //!< The maximum number of persistent (SLAM) features
};

struct InitializerOptions
{
  fp disparity_threshold_;  //!< the disparity threshold for the static initializer
  fp acc_threshold_;        //!< The acceleration threshold for the static initializer
  uint imu_init_window_;    //!< The window in seconds used to check for acceleration spikes
};

struct MSCEqFOptions
{
  StateOptions state_options_;       //!< The state options
  InitializerOptions init_options_;  //!< The initializer options

  fp persistent_feature_init_delay_;  //!< The delay in s before initializing persistent features

  int state_transition_order_;  //!< The order for the computation of the state transition matrix

  fp angular_velocity_std_;       //!< Continuous time angular velocity standard deviation
  fp acceleration_std_;           //!< Continuous time acceleration standard deviation
  fp angular_velocity_bias_std_;  //!< Continuous time angular velocity bias (random walk) standard deviation
  fp acceleration_bias_std_;      //!< Continuous time acceleration bias (random walk) standard deviation

  uint imu_buffer_max_size_;  //!< The maximum size of the propagator's imu buffer

  // FeatureRepresentation msc_features_representation_ =
  //     FeatureRepresentation::ANCHORED_INVERSE_DEPTH;  //!< Multi State Constraint features representation
  // FeatureRepresentation persistent_features_representation_ =
  //     FeatureRepresentation::ANCHORED_INVERSE_DEPTH;  //!< persistent features representation
};

}  // namespace msceqf

#endif  // MSCEQF_OPTIONS_HPP