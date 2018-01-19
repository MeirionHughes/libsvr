let lib = require('bindings')("libsvr");

function make_enum(obj) {
  var new_obj = {};
  for (var prop in obj) {
    if (obj.hasOwnProperty(prop)) {
      new_obj[obj[prop]] = prop;
    }
  }
  return Object.assign(new_obj, obj);
};

const KernelType = make_enum({
  LINEAR: 100,
  POLYNOMIAL: 101,
  RBF: 102,
  RBF_GAUSSIAN: 103,
  RBF_EXPONENTIAL: 104,
  MLP: 105
});

module.exports = {
  KernelType: KernelType,
  OnlineSVR: lib.OnlineSVR
}