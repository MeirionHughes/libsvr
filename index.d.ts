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
  train(vector: number[], value: number): number;
  predict(vector: number[]): number;
}