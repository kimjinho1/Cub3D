#include "cub3d.h"

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	gnl_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	if (dst == 0 || src == 0)
		return (0);
	src_len = gnl_strlen(src);
	if (size > 0)
	{
		while (i < (size - 1) && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = 0;
	}
	return (src_len);
}

size_t	gnl_strlcat(char *dst, const char *src, size_t size)
{
	int		i;
	size_t	dst_len;
	size_t	k;

	i = 0;
	dst_len = gnl_strlen(dst);
	if (size < dst_len)
		k = size;
	else
		k = dst_len;
	while (src[i] && dst_len < size - 1 && size)
		dst[dst_len++] = src[i++];
	while (src[i])
		i++;
	dst[dst_len] = '\0';
	return (i + k);
}

char	*gnl_strdup(const char *s)
{
	char	*str;
	int		i;
	int		slen;

	i = 0;
	slen = (int)gnl_strlen(s);
	str = (char *)malloc(sizeof(char) * (slen + 1));
	if (!(str))
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*str;
	int		s1_len;
	int		s2_len;

	if (s1 == 0 && s2 == 0)
		return (NULL);
	else if (s1 == 0 || s2 == 0)
	{
		if (s1 == 0)
			return (gnl_strdup(s2));
		else
			return (gnl_strdup(s1));
	}
	s1_len = (int)gnl_strlen(s1);
	s2_len = (int)gnl_strlen(s2);
	str = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (!(str))
		return (NULL);
	gnl_strlcpy(str, s1, s1_len + 1);
	free(s1);
	gnl_strlcat(str + s1_len, s2, s2_len + 1);
	return (str);
}
