import { expect } from 'chai';

import libm2 from '../index';

describe("Binding", () => {
  it("should not be undefined", () => {  
    expect(libm2).to.not.be.undefined;
  });
})