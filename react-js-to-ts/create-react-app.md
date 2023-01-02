## Getting Typescript To Work For Create React App

1. Install typescript and types for react
- `npm install typescript @types/react --save-dev`

2. Create tsconfig.json at root.
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

3. Convert your files. This also depends on your code.
- Convert `.js` or `.jsx` extension to `.tsx`
- Add types to your props and states
- Download types for your react dependencies. This depends on your project. 

You can find the list of types here: https://www.npmjs.com/~types