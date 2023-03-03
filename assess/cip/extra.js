
const Test = () => {
        const [personData, setPersonData] = useState(null);
        const url = 'http://localhost:5000'
    
    const getData = () => {

        const {data} = axios.get(`${url}/getPerson`, {
            params: {
                name: "bon",
            }
        })
        .then((response) => {
            setPersonData(response.data);
            console.log(response.data);
        })
        .then((error) => {
            console.log(error);
        }) 
    }

    useEffect(() => {
        getData();
    }, [])

    return (
        <div>
        </div>
)}

export default Test;

app.get('/getPerson', async (req, res) => {
    const name = req.query.name;
    
    var value;
    const testQuery = `select * from "JONATHAN.TROST".PERSON where (CRASH_ID = 12529587)`
    const otherTesteQuery = `select * from "JONATHAN.TROST".PERSON where (CRASH_ID = 12488166)`
    async function fetchPerson() {
      try {
        const connection = await oracledb.getConnection({ 
          user: process.env.USER_NAME, 
          password: process.env.DB_PASSWORD, 
          connectionString: process.env.DB_URL 
        });



        oracledb.outFormat = oracledb.OUT_FORMAT_ARRAY;
        if (name == 'jon') {
          value = '12488166'
        }
        else if (name == 'Jon') {
          value = '123'
        }
        else {
          value = '12529587'
        }
        const testQueryAgain = `select * from "JONATHAN.TROST".PERSON where (CRASH_ID = ${value})`
        const result = await connection.execute(testQueryAgain);
        return result;

      } 
      catch(error) {
        return error;
      }
    }
