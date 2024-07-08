export async function Fetch({
  command,
  args = {}
}) {
  let str = encodeURIComponent("json") + '=' + encodeURIComponent(JSON.stringify({command, args}));
  let json;

  try {
    let res = await fetch(
      process.env.REACT_APP_API_URL,
      {
        method: 'POST',
        body: str,
        headers: {
            'Content-Type': 'application/x-www-form-urlencoded',
        },
        referrer: "",
        credentials: 'include',
      }
    );
    json = await res.json();

    if (!res.ok) {
      throw Error(res.statusText);
    }

    if (json.status == "error") {
      throw Error(json.error);
    }
  } catch (err) {
    return Promise.reject(err);
  }

  return json;
}