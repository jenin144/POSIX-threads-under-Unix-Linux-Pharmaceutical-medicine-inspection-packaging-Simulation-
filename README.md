# Pharmaceutical medicine inspection & packaging Simulation using multithreading and multiprocessing aprroch with shardmemory, queues ,and fifosز 🏭💊

## Overview

A comprehensive real-time simulation of a pharmaceutical manufacturing facility that produces and quality-checks both liquid and pill medications. The system demonstrates advanced concepts in concurrent programming, inter-process communication, and dynamic resource management using Linux system programming.

## Project Description

This simulation models a medicine factory with multiple production lines operating simultaneously. The factory produces two types of medicines:
- **Liquid Medicines**: Bottled medications with specific volume, color, and packaging requirements
- **Pill Medicines**: Tablet medications in containers with size, color, and quantity specifications

### Key Concepts Demonstrated

- **Multi-Process Architecture**: Parent-child process hierarchies
- **Multi-Threading**: Worker threads performing concurrent quality inspection
- **Inter-Process Communication (IPC)**:
  - Shared Memory for data exchange
  - Signals for process coordination
  - Semaphores and Mutexes for synchronization
- **Dynamic Resource Management**: Automatic worker thread allocation based on performance
- **Real-Time Monitoring**: Visual feedback through OpenGL interface


## Key Features

### 🔄 Concurrent Processing
- Multiple production lines operate simultaneously
- Each line has multiple worker threads
- True parallel execution on multi-core systems

### 🎯 Quality Control
- Rigorous inspection of every sample
- Multiple quality criteria must be satisfied
- Automatic rejection of defective products

### 📊 Real-Time Statistics
- Per-line tracking of checked, approved, packaged samples
- Global statistics across all production lines
- Performance metrics for optimization decisions

### 🔧 Dynamic Adaptation
- Automatic worker allocation based on need
- Load balancing across production lines
- Responsive to changing production demands

### 🖥️ Visual Monitoring
- OpenGL-based real-time visualization
- Color-coded status indicators
- Interactive production monitoring

## Usage
Run:  makefile



## File Structure
https://github.com/user-attachments/assets/85dc89db-7b08-4159-9270-68a213034a9f
