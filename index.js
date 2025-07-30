/*>
 * import the postgres module and retreive from it the defined class 'Client' */
const { Client } = require('pg')

/* Create a new instance of the client from the import class Client */
const  client = new Client({
    user : "",
    password : "",
    host: "",
    port: 0,
    database: "",
});


/*>
 * Call the method "connect" to establish connection with server that host
 * postgres. 
 * Note that this methods returns a promise and subsequent command are 
 * executed by chaining them with method 'then' */
client.connect()
.then( ()=> console.log("Connected successfully..."))
/*>
 * This query fetches the complete table (public.baecat_baecatuser)
 * --
 *.then( ()=> client.query("select * from public.baecat_baecatuser")) */

/*>
 * This query fetches the from table (public.baecat_baecatuser) an entry with id = 1
 * --*/
.then( ()=> client.query("select * from public.baecat_baecatuser where id = $1", ["1"]))
.then( (result)=> console.table(result.rows))
.catch( (e)=> console.log(e))
.finally( ()=>client.end())