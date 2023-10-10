const express = require('express')
const app = express()
const port = 3000

const path = require('path')
let publicPath = path.resolve(__dirname, "public")
app.use(express.static(publicPath))

app.listen(port, () => console.log(`assignment 1 server listening on port ${port}`))

