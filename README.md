# 🌱 AeroCure — Mold Risk Detection & Prevention System

## 📌 Overview

**AeroCure** is an Arduino-based environmental monitoring system designed to **detect and prevent mold-conducive conditions indoors**.

This repository contains our **first working prototype (v1)**, which focuses on sensing temperature and humidity and estimating mold risk using a rule-based model.

This version serves as the **foundation for future iterations**, where AeroCure will evolve into an **active, data-driven system** capable of intervention and prediction.

---

## ⚙️ Prototype v1 Features (Current)

* Real-time sensing:

  * Ambient temperature & humidity via DHT11
  * Surface/wall temperature via thermistor
* LCD display (I2C):

  * Temperature, humidity, and risk status
* LED indicators:

  * 🟢 Low risk
  * 🟡 Moderate risk
  * 🔴 High risk
* Serial output for:

  * Debugging
  * External data collection

---

## 🧠 Mold Risk Logic (Baseline Model)

This prototype uses a simple threshold-based system:

* **High Risk**

  * Humidity > 70%

* **Moderate Risk**

  * Humidity > 50% AND temperature between 21–30°C

* **Low Risk**

  * All other conditions

This serves as a **baseline approximation**, not a definitive mold detection model yet. The model is our future direction

---

## 🔌 Hardware Components

* Arduino (Uno or compatible)
* DHT11
* 10kΩ Thermistor
* 16x2 I2C LCD display
* LEDs (green, yellow, red)
* Resistors, jumper wires, breadboard

---

## 🖥️ Output & Data Flow

* **LCD Display**

  * Live environmental readings
  * Mold risk classification
* **LED Indicators**

  * Visual risk feedback
* **Serial Output**

  * Structured data for logging and visualization

---

## 🚧 Limitations (v1)

* No data storage or logging
* No graphical interface
* Limited sensor accuracy (DHT11), (No other sensor Markers)
* Static threshold-based logic (no learning)
* No active environmental control

---

## 🚀 Roadmap — Future Iterations

### 🔧 Prototype v2 — Active Control

We will transition AeroCure from passive monitoring to **active prevention**:

* Integrate a fan module
* Automatically reduce humidity and stagnation
* Trigger airflow based on risk conditions

---

### 🌐 Prototype v3 — Data Logging & GUI

We will build a data pipeline for visualization and analysis:

* Live plotting using Matplotlib
* Local or cloud-based data storage
* Web-based dashboard (e.g., using Flask)
* Historical trend tracking

---

### 🧠 Prototype v4 — Machine Learning Prediction

We aim to replace static thresholds with a **data-driven predictive model**:

* Develop a dataset from collected environmental data
* Train models using:

  * Time-series features (e.g., humidity duration, rate of change)
* Deploy lightweight models using Impulse AI

⚠️ Note: Public datasets on indoor air quality rarely include labeled mold growth data. Our approach focuses on **learning patterns of mold-conducive conditions**, not direct mold detection.

---

## 🧩 System Evolution

| Version | Capability                         |
| ------- | ---------------------------------- |
| v1      | Passive sensing & threshold logic  |
| v2      | Active environmental control (fan) |
| v3      | Data logging & visualization       |
| v4      | Predictive machine learning        |

---

## 🎯 Project Goal

Rather than reacting to visible mold, AeroCure aims to:

> **Predict and prevent mold-conducive conditions before growth occurs**

This approach supports:

* Healthier indoor environments
* Preventative maintenance
* Sustainable building practices

---

## 📁 Repository Structure

```bash
/Arduino
  └── Prototypev1_AeroCure.ino

/Python (future, not here yet)
  ├── 

/docs
  └──
```

---

## 👥 Contributors

* Avriza Devano
* Anjali Tholudur
* Annabelle Duink
* Matthew Hwang

---

## 📌 Project Status

✅ Prototype v1 complete
🔄 Active development in progress

This repository will continue to evolve as AeroCure transitions into a fully integrated **smart environmental system**.
