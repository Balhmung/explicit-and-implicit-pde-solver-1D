# 1D Heat Conduction Solver (C++)

A modular C++ computational framework for solving the **one-dimensional transient heat conduction equation** using multiple finite-difference schemes (explicit and implicit).  
The project benchmarks numerical solutions against an analytical reference and evaluates **stability, accuracy, and convergence**.

---

## Table of Contents
- [Project Overview](#project-overview)
- [Physical Problem](#physical-problem)
- [Governing Equation](#governing-equation)
- [Geometry and Conditions](#geometry-and-conditions)
- [Analytical Solution](#analytical-solution)
- [Numerical Methods](#numerical-methods)
- [Software Architecture](#software-architecture)
- [Core Classes](#core-classes)
- [UML Architecture Diagram](#uml-architecture-diagram)
- [Design Principles](#design-principles)
- [Validation Strategy](#validation-strategy)
- [Libraries Used](#libraries-used)
- [References](#references)

---

## Project Overview

This project implements and compares multiple numerical schemes to solve a **1D transient heat transfer problem** in a solid wall subjected to sudden boundary temperature changes.

Implemented schemes:
- Richardson Explicit Scheme
- DuFort–Frankel Scheme
- Laasonen Implicit Scheme
- Crank–Nicolson Scheme

All numerical results are benchmarked against a closed-form analytical solution.

---

## Physical Problem

The objective is to compute the transient temperature distribution inside a one-dimensional wall after imposing fixed boundary temperatures.

Applications include:
- thermal analysis of solid materials,
- engineering heat-transfer studies,
- numerical-method benchmarking and education.

---

## Governing Equation

The one-dimensional transient heat conduction equation is:

**∂T/∂t = D ∂²T/∂x²**

Where:
- **T(x,t)** is the temperature,
- **D** is the thermal diffusivity,
- **x** is the spatial coordinate,
- **t** is time.

---

## Geometry and Conditions

**Domain**
- 1D wall of length **L = 0.31 m**

**Material Property**
- Thermal diffusivity: **D = 93 cm²/hr**

**Initial Condition**
- Temperature at start : **T(x,0) = 38°C**


**Boundary Conditions (Dirichlet)**
- Temperature at starting position **T(0,t) = T(L,t) = 149°C**


**Spatial Discretization**
- Spatial step: **Δx = 0.05 m**

---

## Analytical Solution

The analytical solution used for validation is:

- **T(x, t)** is the temperature at position *x* and time *t*
- **T_sur** is the imposed surface temperature
- **T_in** is the initial uniform temperature
- **D** is the thermal diffusivity
- **L** is the wall length
- **m** is the Fourier series index

This solution provides a reference temperature at any position \(x\) and time \(t\).

---

## Numerical Methods

### Richardson Explicit Scheme
- Second-order in space and time
- Conditionally stable
- Stability condition:
- 
  **r = D · Δt / (Δx)² ≤ 1**

Where:
- **r** is the stability parameter,
- **D** is the thermal diffusivity,
- **Δt** is the time step,
- **Δx** is the spatial step.

---

### DuFort–Frankel Scheme
- Explicit, three time levels
- Unconditionally stable
- Introduces artificial diffusion
- Boundary conditions enforced using the Hoffmann method

---

### Laasonen Implicit Scheme
- Fully implicit
- Unconditionally stable
- Requires solving a tridiagonal linear system at each time step

---

### Crank–Nicolson Scheme
- Second-order in space and time
- Unconditionally stable
- Combines stability of implicit schemes with accuracy of explicit schemes
- Recommended for general use

---

## Software Architecture

The code follows a **modular object-oriented design**, separating:
- physical definitions,
- grid representation,
- numerical schemes,
- simulation control,
- output management.

Key design goals:
- extensibility,
- maintainability,
- clear separation of concerns,
- runtime interchangeability of numerical schemes.

---

## Core Classes

### `Grid1D`
Represents the one-dimensional spatial domain.
- Stores grid coordinates and spacing
- Centralizes geometry handling

---

### `HeatProblem`
Encapsulates physical parameters.
- Diffusivity
- Initial and boundary conditions
- Initial temperature vector generation

---

### `TimeScheme` (Abstract)
Base class for all time-integration schemes.
- Defines the `step()` interface
- Enables polymorphism and runtime selection

---

### `RichardsonScheme`
Implements the Richardson explicit scheme.
- Included mainly for comparison and instability illustration

---

### `DuFortFrankelScheme`
Implements the DuFort–Frankel explicit scheme.
- Improved stability
- Uses three time levels

---

### `LaasonenScheme`
Implements the Laasonen implicit scheme.
- Uses a tridiagonal linear solver

---

### `CrankNicolsonScheme`
Implements the Crank–Nicolson scheme.
- High accuracy and stability
- Closest to analytical solution for reasonable time steps

---

### `TridiagonalSolver`
Utility class implementing the Thomas algorithm.
- Forward elimination
- Backward substitution
- Shared by implicit schemes

---

### `AnalyticalSolution`
Provides evaluation of the analytical temperature solution at any \(x,t\).

---

### `Simulation`
Central orchestrator.
- Manages time loop
- Advances numerical schemes
- Updates temperature fields
- Delegates output to `OutputManager`

---

### `OutputManager`
Handles all output operations.
- Directory creation
- CSV file writing
- Exports numerical and analytical data
- Designed for MATLAB / Python post-processing

---

## UML Architecture Diagram

The full class architecture and relationships are illustrated below:

![UML Architecture Diagram]

<img width="1540" height="764" alt="UML_graph" src="https://github.com/user-attachments/assets/7ae40d41-f1fb-4afe-8527-4f11639c88b5" />

*(Composition, inheritance, aggregation, and usage relationships are explicitly represented.)*

---

## Design Principles

The code follows **SOLID principles**:

- **SRP** – Each class has one responsibility
- **OCP** – New schemes can be added without modifying existing code
- **LSP** – All schemes are interchangeable via `TimeScheme`
- **ISP** – Minimal, purpose-driven interfaces
- **DIP** – High-level modules depend on abstractions

---

## Validation Strategy

- Numerical results are compared against the analytical solution
- Explicit schemes exhibit CFL-related instability when limits are exceeded
- Implicit schemes show superior robustness and convergence
- Crank–Nicolson provides the best accuracy-to-cost tradeoff

---

## Libraries Used

- `<iostream>` – console interaction
- `<fstream>` – CSV file writing
- `<vector>` – numerical data storage
- `<cmath>` – mathematical functions
- `<memory>` – smart pointers and polymorphism
- `<string>` – filename and scheme naming
- `<sstream>`, `<iomanip>` – formatted output
- `<filesystem>` – directory handling
- `<stdexcept>` – exception handling
- `<utility>` – move semantics
- `#pragma once` – header guard optimization

---

## References

1. K. A. Hoffmann and S. T. Chiang,  
   *Computational Fluid Dynamics*, Fourth Edition, Vol. I,  
   Engineering Education System Books.

2. Scott Collis,  
   *An Introduction to Numerical Analysis for Computational Fluid Dynamics*,  
   Technical Report SAND2005-2745, Sandia National Laboratories, 2005.

---

*No computers or coffee machines were (almost) harmed in the making of this code.*

