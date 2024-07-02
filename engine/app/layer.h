// ==========================================================================
// UNLIMITED RIGHTS
// Contract No. W900KK-23-D-0001/W900KK-23-F-00023
// [Flight School Training Support Services (FSTSS)]
//
// Contractor Name: Applied Visual Technology, Inc.
//                  (d/b/a AVT Simulation)
//
// Contractor Address: 4715 Data Court
//                     Orlando, Florida 32817
//
// SECURITY CLASSIFICATION: Unclassified
//
// WARNING: This software contains data whose export is restricted by the Arms
// Export Control Act (Title 22, U.S.C., Section 2751 et seq.) or the Export
// Administration Act of 1979, as amended, Title 50, U.S.C, APP. 2401 et seq.
//
// Copyright © 2023, 2024
// Applied Visual Technology, Inc. (d/b/a AVT Simulation)
// Unpublished Work - All Rights Reserved
// ==========================================================================
#pragma once

#include <memory>

class Layer {
public:
  virtual ~Layer() = default;

  virtual void update(){};
  virtual void render(){};
};

using LayerPtr = std::shared_ptr<Layer>;
