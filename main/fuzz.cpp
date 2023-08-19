#include "../src/cpu/cpu.hpp"
#include "../src/memory/lambda_memory.hpp"
#include <array>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>

std::array<uint8_t, 40> test_impl(std::array<uint8_t, 16> pInput) {
  std::array<uint8_t, 40> output;
  output.fill(0);
  int readPos = 12;
  int writePos = 16;
  cpu::cpu cpuSut(std::make_shared<memory::lambda_memory>(
      [&](uint16_t pAddr) {
        auto readValue = pInput[readPos];
        output[writePos] = pAddr & 0xff;
        output[writePos + 1] = (pAddr >> 8) & 0xff;
        output[writePos + 2] = 1;
        output[writePos + 3] = readValue;
        writePos += 4;
        readPos += 1;
        return readValue;
      },
      [&](uint16_t pAddr, uint8_t pValue) {
        output[writePos] = pAddr & 0xff;
        output[writePos + 1] = (pAddr >> 8) & 0xff;
        output[writePos + 2] = 2;
        output[writePos + 3] = pValue;
        writePos += 4;
      }));
  cpuSut.mRegister.a = pInput[0];
  cpuSut.mRegister.b = pInput[1];
  cpuSut.mRegister.c = pInput[2];
  cpuSut.mRegister.d = pInput[3];
  cpuSut.mRegister.e = pInput[4];
  cpuSut.mRegister.f = pInput[5];
  cpuSut.mRegister.h = pInput[6];
  cpuSut.mRegister.l = pInput[7];
  cpuSut.mRegister.pc = pInput[8] | (pInput[9] << 8);
  cpuSut.mRegister.sp = pInput[10] | (pInput[11] << 8);
  cpuSut.mClocks = 0;
  cpuSut.step();
  output[0] = cpuSut.mRegister.a;
  output[1] = cpuSut.mRegister.b;
  output[2] = cpuSut.mRegister.c;
  output[3] = cpuSut.mRegister.d;
  output[4] = cpuSut.mRegister.e;
  output[5] = cpuSut.mRegister.f;
  output[6] = cpuSut.mRegister.h;
  output[7] = cpuSut.mRegister.l;
  output[8] = cpuSut.mRegister.pc & 0xff;
  output[9] = (cpuSut.mRegister.pc >> 8) & 0xff;
  output[10] = cpuSut.mRegister.sp & 0xff;
  output[11] = (cpuSut.mRegister.sp >> 8) & 0xff;
  output[12] = cpuSut.mClocks;
  return output;
}

int main() {
  while (true) {
    std::string inputStr;
    std::array<uint8_t, 16> inputBuf;
    std::cin >> inputStr;
    // Input
    for (auto i = 0; i < inputStr.length(); i += 2) {
      if (i >= 16 * 2)
        break;
      std::string byteStr = inputStr.substr(i, 2);
      char byte = strtol(byteStr.c_str(), NULL, 16);
      inputBuf[i / 2] = byte;
    }
    auto outputBuf = test_impl(inputBuf);
    // Output
    std::cout << std::hex;
    for (int i = 0; i < outputBuf.size(); i++) {
      std::cout << std::setw(2) << std::setfill('0') << (int)outputBuf[i];
    }
    std::cout << std::endl;
  }
  return 0;
}
