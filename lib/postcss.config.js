const fs = require('fs')
module.exports = {
  plugins: [
    require('postcss-modules')({
        getJSON: (cssFN, json, outputFN) => {
            fs.writeFileSync(outputFN + ".json", JSON.stringify(json))
        }
    }),
  ],
}