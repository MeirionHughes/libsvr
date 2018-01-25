export enum KernelType {
  LINEAR = 100,
  POLYNOMIAL = 101,
  RBF = 102,
  RBF_GAUSSIAN = 103,
  RBF_EXPONENTIAL = 104,
  MLP = 105
}

export class OnlineSVR {
  constructor();
  clear();
  train(vector: number[], value: number): number;
  predict(vector: number[]): number;
  forget(index: number[]): void;
  setC(c: number): void;
  getC(): number;;
  setEpsilon(epsilon: number): void;
  getEpsilon(): number;
  setKernel(type: KernelType): void;
  getKernel(): KernelType;
  setKernelParam(param: number): void;
  getKernelParam(): number;

  getSamplesTrainedNumber():number;
  getSupportSetElementsNumber():number;
  getErrorSetElementsNumber():number;
  getRemainingSetElementsNumber():number;

  getSupportSetIndexes():number[];
  getErrorSetIndexes():number[];
  getRemainingSetIndexes():number[];
}