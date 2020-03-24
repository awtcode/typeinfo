  Module["mmh"] = function() {
    FS.mkdir('/output'); 
    if (ENVIRONMENT_IS_NODE) {
      FS.mount(NODEFS, {
        root: 'C:/git/typeinfo/build/'
      }, '/output');
      var sideExists = FS.analyzePath("/output/side.wasm").exists;
        console.log("mmh sideExists:" + sideExists);
        loadDynamicLibrary("/output/side.wasm", {global: true, nodelete: true, fs:FS});
    } else {
      FS.createPreloadedFile('/output', 'side.wasm', "http://localhost:8080/side.wasm", true, true, () => {
        var sideExists = FS.analyzePath("/output/side.wasm").exists;
        console.log("mmh sideExists:" + sideExists);
        loadDynamicLibrary("/output/side.wasm", {global: true, nodelete: true, fs:FS});
      });
    }
  }

Module['preRun'] = function() {
  Module["mmh"]();
}

var postTestMessage = function(message)  {
      console.log('msg:' + message);
  }