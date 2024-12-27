// const displayRotate = require('./build/Release/display-rotate.node')
// module.exports = displayRotate

// Will load a compiled build if present or a prebuild.
// If no build if found it will throw an exception
const binding = require("node-gyp-build")(__dirname);
module.exports = binding;
