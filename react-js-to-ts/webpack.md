## Getting Typescript To Work For Own Webpack Config

To get typescript running for a webpack build.

[Webpack Documentation](https://webpack.js.org/guides/typescript/)

1. Install typescript, ts-loader, and types for react
- `npm install typescript ts-loader @types/react --save-dev`
2. Create `tsconfig.json` at root.
- Below is a sample of compiler options for typescript

```
{
  "compilerOptions": {
    "outDir": "./dist/",
    "noImplicitAny": true,
    "module": "es6",
    "allowSyntheticDefaultImports": true,
    "target": "es5",
    "jsx": "react",
    "allowJs": true,
    "moduleResolution": "node"
  }
}
```

3. Modify webpack file
- Below is a sample of what the webpack file should look like.
- Need the `resolve` object and rule for `.tsx`

```
const path = require("path");
const webpack = require("webpack");
const HTMLWebpackPlugin = require("html-webpack-plugin");

module.exports = {
  entry: "./index.js",
  output: {
    filename: "bundle.js",
    path: path.resolve("dist"),
    publicPath: "/",
  },
  resolve: {
    extensions: ['.tsx', '.ts', '.js'],
  },
  module: {
    rules:[
      {
        test: /\.tsx?$/,
        use: 'ts-loader',
        exclude: /node_modules/,
      },
    ], 
  },  
  plugins: [
    new HTMLWebpackPlugin({
      template: "index.html"
    }),
  ]
}
```

4. Convert your files. This also depends on your code.
- Convert `.js` or `.jsx` extension to `.tsx`
- Add types to your props and states
- Download types for your react dependencies. This depends on your project. 

You can find the list of types here: https://www.npmjs.com/~types