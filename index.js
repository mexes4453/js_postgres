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
 * ----------------
 * Query: 1 - Fetch
 * ----------------
 * This query fetches the complete table (public.baecat_baecatuser)
 * command to fetch query :  .then( ()=> client.query(queryTxt))
 * -- */
//const queryTxt = "select * from public.baecat_baecatuser";

/*>
 * ----------------
 * Query: 2 - Fetch
 * ----------------
 * This query fetches the from table (public.baecat_baecatuser) an entry with id = 1
 * Note that the same query can be written as below.
 * const queryTxt = "select * from public.baecat_baecatuser where id = 1";
 * but this approach is prone to sql injection by hackers.
 * command to fetch query :  .then( ()=> client.query(queryTxt, ["1"]))
 * --*/
//const queryTxt = "select * from public.baecat_baecatuser where id = $1";
const queryTxt = "insert into public.baecat_baecatuser(bio, birth_date, sex, \
                                                              thumbnail_image_path, \
                                                              stream_key, \
                                                              live_at_tmz, \
                                                              country_name, \
                                                              tokens, \
                                                              current_amount_of_views, \
                                                              is_streaming, \
                                                              user_id) values($1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11)";


/*>
 * Call the method "connect" to establish connection with server that host
 * postgres. 
 * Note that this methods returns a promise and subsequent command are 
 * executed by chaining them with method 'then' */
/*
client.connect()
.then( ()=> console.log("Connected successfully..."))
.then( ()=> client.query(queryTxt, ["1"]))
.then( (result)=> console.table(result.rows))
.catch( (e)=> console.log(e))
.finally( ()=>client.end()) */
/*>
 * Alternatively, the above command can be performed in an async fashion.
 */
async function PG_Query(qTxt, qValue)
{
    try
    {
       await client.connect()
       console.log("Connected successfully...")
       const result = await client.query(qTxt, qValue);
       console.table(result.rows)
    }
    catch(e)
    {
       console.log("Error!", e)
    }
    finally
    {
       await client.end()
       console.log("Client disconnected successfully.")
    }
}



//PG_Query(queryTxt, ["51"]); /* fetch */
PG_Query(queryTxt, ['', null, '', '', 'test123456', 'UTC', null, 212, 0, false, 51]); /* insert */



/* Not used */
class PgQuery
{
    constructor(n, q, v)
    {
       this.name = n;
       this.query = q;
       this.value = v;
    }
}
