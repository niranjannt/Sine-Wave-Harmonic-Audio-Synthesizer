# Lab 5: Digital Music Player with TLV5616 DAC and LM4890 Audio Amplifier  

## Team Size
2  

## Project Overview
This lab demonstrates how to generate analog audio signals from a microcontroller using a **12-bit TLV5616 DAC** and an **LM4890 audio amplifier**. The system stores music as a data structure, sends digital values to the DAC over **SSI1**, and drives an **8Ω speaker**.  

Key features:
- High-quality analog waveform generation from digital data  
- Modular software with separate drivers for DAC, switches, and music playback  
- Timer interrupts for precise waveform timing  
- Audio output through a speaker with configurable gain  

---

## Hardware
- **Microcontroller**: EK-TM4C123GXL  
- **DAC**: TLV5616C 12-bit (single, SSI interface)  
- **Audio Amplifier**: LM4890M  
- **Voltage Reference**: LM4041CILPR  
- **Speaker**: 8Ω  
- **Passive components**: Resistors, capacitors as required  

### TLV5616C SSI Pin Connections
- **SSIClk (SCLK)** → PD0  
- **SSIFss (FS)** → PD1  
- **SSITx (DIN)** → PD3  

> The SSI module is configured to match the TLV5616 timing: **SPO=1, SPH=0, SCR=0, CPSDVSR=8, DSS=16-bit**.  

---

## Software Overview
- **DAC driver**: `DAC.h` / `DAC.c`  
  - `DAC_Init(uint16_t data)` – initializes SSI1 and sets initial DAC output  
  - `DAC_Out(uint16_t code)` – sends a 12-bit value to the DAC  
- **Switch driver**: `Switch.h` / `Switch.c` for user input  
- **Music player module**: `Music.h` / `Music.c`  
  - Stores song as a structured array of notes and durations  
  - Handles playback using timer interrupts  

---

## Project Goals
- Understand DACs and voltage references  
- Create SSI communication with correct timing for TLV5616  
- Design and implement modular software for music playback  
- Drive a speaker with an audio amplifier to produce high-quality sound  

---

## Procedure
1. **Write low-level drivers**
   - Implement DAC initialization and data transmission over SSI1  
   - Implement switch interface for controlling playback  

2. **Design music data structure**
   - Store notes, durations, and optional rests or envelopes  
   - Implement `Music_Play()` to stream data to DAC using interrupts  

3. **Assemble DAC and voltage reference**
   - Connect TLV5616C to TM4C123GXL using SSI1 pins  
   - Build voltage reference circuit using **LM4041CILPR** for stable DAC output  

4. **Build audio amplifier**
   - Solder LM4890 to a breakout board  
   - Connect amplifier output to the 8Ω speaker  

5. **Debug and test**
   - Verify DAC output matches expected values  
   - Listen to the music playback and tune amplifier gain for linearity  
   - Optional: Enclose speaker to enhance sound quality  

---

## References
- [TLV5616C Datasheet](https://www.ti.com/lit/ds/symlink/tlv5616.pdf)  
- [LM4890 Datasheet](https://www.ti.com/lit/ds/symlink/lm4890.pdf)  
- [LM4041 Voltage Reference Datasheet](https://www.ti.com/lit/ds/symlink/lm4041.pdf)  
- TM4C123GXL Periodic Timer and SSI example projects  

---

## Notes
- Only the **TLV5616C DAC** and **LM4041CILPR voltage reference** are used in this project.  
- Sound quality is prioritized over loudness.  
- Factors affecting quality:
  - DAC precision and linearity  
  - Amplifier gain and frequency response  
  - DAC update rate and interrupt jitter  
  - Complexity of the stored music data  
