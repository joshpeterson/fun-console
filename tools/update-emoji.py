import urllib.request

# From https://stackoverflow.com/questions/7243750/download-file-from-web-in-python-3
url = 'https://unicode.org/Public/emoji/13.0/emoji-test.txt'
response = urllib.request.urlopen(url)
data = response.read()
text = data.decode('utf-8')

lines = text.splitlines()

for line in lines:
  if line.startswith("#"):
    continue
  parts = line.split(";")
  if len(parts) == 2:
    emoji_version_string_index = parts[1].find("E")
    start_of_name_index = parts[1].find(" ", emoji_version_string_index + 1)
    name = parts[1][start_of_name_index + 1:]

    code = 'u8"'
    code_parts = parts[0].strip().split(" ")
    for code_part in code_parts:
      padded_code = code_part.rjust(8, "0")
      code += '\\U' + padded_code

    code += '"'
    print(f'{{"{name}", {code}}},')


